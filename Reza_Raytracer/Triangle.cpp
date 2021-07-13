#include "Triangle.h"

#include <limits>

/*
www.scratchapixel.com/lessons/3d-basic-rendering/
ray-tracing-rendering-a-triangle/
moller-trumbore-ray-triangle-intersection
*/

/*
github.com/mattgodbolt/pt-three-ways/
blob/main/src/oo/Triangle.cpp
*/
bool Triangle::Hit(const Ray3& r, double t_min, double t_max, HitRecord& rec) const
{	
    // can be precomputed
    //Vec3 v0v1 = v1 - v0;
    //Vec3 v0v2 = v2 - v0;

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

    constexpr double epsilon = std::numeric_limits<double>::epsilon();
	    
    // if the determinant is close to 0, the ray misses the triangle
    if (abs(det) < epsilon)
    {
        return false;
    }

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
    rec.t = t;	

    // calculate normal, warning, this is not a unit vector
    Vec3 outward_normal;
    
    // Normal
    double w = 1.0 - u - v;
    outward_normal = (n0 * w) + (n1 * u) + (n2 * v); 

    // if the determinant is negative the triangle is backfacing
    //bool backfacing = det < epsilon; // won't give correct result if we have vertex normals
    //rec.front_face = backfacing;
    rec.front_face = Dot(r.Direction(), outward_normal) < 0;
    
    if (!rec.front_face)
    {
        outward_normal = -outward_normal;
    }

    // set normal
    rec.normal = outward_normal;

    // Raw pointer
    rec.mat_ptr = material_ptr.get();
    rec.p = r.At(t);

    // uv
    Vec2 uv = GetTriangleUV(u, v, w);
    rec.u = uv.x();
    rec.v = uv.y();

    return true;
}

bool Triangle::BoundingBox(AABB& output_box) const
{
    // need to pad the AABB to avoid zero thickness
    // TODO: experiment with thinner pads
    Vec3 padding(1e-5, 1e-5, 1e-5);
    
    Vec3 min(fmin(v0.x(), fmin(v1.x(), v2.x())),
			 fmin(v0.y(), fmin(v1.y(), v2.y())),
			 fmin(v0.z(), fmin(v1.z(), v2.z())));

    min = min - padding;

    Vec3 max(fmax(v0.x(), fmax(v1.x(), v2.x())),
             fmax(v0.y(), fmax(v1.y(), v2.y())),
             fmax(v0.z(), fmax(v1.z(), v2.z())));

    max = max + padding;

    /*constexpr double eps = std::numeric_limits<double>::epsilon();
    Vec3 padding(0, 0, 0);

    if (abs(min.x() - max.x()) < eps )
    {
        padding.e[0] = 1e-5;
    }

    if (abs(min.y() - max.y()) < eps)
    {
        padding.e[1] = 1e-5;
    }

    if (abs(min.z() - max.z()) < eps)
    {
        padding.e[2] = 1e-5;
    }
	
    min = min - padding;
    max = max - padding;*/

    output_box = AABB(min, max);

    return true;
}

Vec2 Triangle::GetTriangleUV(double u, double v, double w) const
{
    return (uv0 * w) + (uv1 * u) + (uv2 * v);
}