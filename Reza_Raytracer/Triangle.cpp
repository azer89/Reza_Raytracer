
#include "Triangle.h"

bool Triangle::Hit(const Ray3& r, double t_min, double t_max, HitRecord& rec) const
{
    /*
    www.scratchapixel.com/lessons/3d-basic-rendering/
    ray-tracing-rendering-a-triangle/
    moller-trumbore-ray-triangle-intersection
    */
	
	// can be precomputed
    Vec3 v0v1 = v1 - v0;
    Vec3 v0v2 = v2 - v0;

	// scalar triple product
	/*
	You have three vectors

        a1      b1      c1
    a = a2  b = b2  c = c2
        a3      b3      c3
	
        |a1 b2 c1|
    det |a2 b2 c2| = (a x b) . c
        |a3 b3 c3|

	x is cross product, . is dot product
	*/
    Vec3 pvec = Cross(r.Direction(), v0v2);
    double det = Dot(v0v1, pvec); 

    constexpr double kEpsilon = std::numeric_limits<double>::epsilon();
	
	//#ifdef CULLING 
	// if the determinant is negative the triangle is backfacing
	// if the determinant is close to 0, the ray misses the triangle
    if (det < kEpsilon)
    {
        return false;
    }
	//#else 
    // ray and triangle are parallel if det is close to 0
	// fabs is extremely slow
    /*if (fabs(det) < kEpsilon)
    {
        return false;
    }*/
	//#endif

    double invDet = 1 / det;

    Vec3 tvec = r.Origin() - v0;
    double u = Dot(tvec, pvec) * invDet; 
    if (u < 0 || u > 1)
    {
        return false;
    }

    Vec3 qvec = Cross(tvec, v0v1);     
    double v = Dot(r.Direction(), qvec) * invDet; 
    if (v < 0 || u + v > 1)
    {
        return false;
    }

    double t = Dot(v0v2, qvec) * invDet;

	// For multiple objects, we take the closest one
    if (t < t_min || t_max < t)
    {
        return false;
    }
	
    // Hit Record
    rec.u = u;
    rec.v = v;
    rec.t = t;	
    auto outward_normal = Cross(v0v1, v0v2);
    rec.SetFaceNormal(r, outward_normal);
    rec.mat_ptr = mp;
    rec.p = r.At(t);

    return true;
}

bool Triangle::BoundingBox(AABB& output_box) const
{
    Vec3 min(fmin(v0.x(), fmin(v1.x(), v2.x())),
			 fmin(v0.y(), fmin(v1.y(), v2.y())), 
			 fmin(v0.z(), fmin(v1.z(), v2.z())));

    Vec3 max(fmax(v0.x(), fmax(v1.x(), v2.x())),
             fmax(v0.y(), fmax(v1.y(), v2.y())),
             fmax(v0.z(), fmax(v1.z(), v2.z())));
	
    output_box = AABB(min, max);

    return true;
}