
#include "Triangle.h"

bool Triangle::Hit(const Ray3& r, double t_min, double t_max, HitRecord& rec) const
{
    // www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-rendering-a-triangle/moller-trumbore-ray-triangle-intersection
	
	// can be precomputed
    Vec3 v0v1 = v1 - v0;
    Vec3 v0v2 = v2 - v0;
    Vec3 pvec = Cross(r.Direction(), v0v2);  // dir.crossProduct(v0v2);
    double det = Dot(v0v1, pvec);          // v0v1.dotProduct(pvec);

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
	// fabs is extremely slow!
    /*if (fabs(det) < kEpsilon)
    {
        return false;
    }*/
	//#endif

    double invDet = 1 / det;

    Vec3 tvec = r.Origin() - v0;             //  orig - v0;
    double u = Dot(tvec, pvec) * invDet; // tvec.dotProduct(pvec)* invDet;
    if (u < 0 || u > 1)
    {
        return false;
    }

    Vec3 qvec = Cross(tvec, v0v1);                  // tvec.crossProduct(v0v1);
    double v = Dot(r.Direction(), qvec) * invDet; // dir.dotProduct(qvec)* invDet;
    if (v < 0 || u + v > 1)
    {
        return false;
    }

    double t = Dot(v0v2, qvec) * invDet; // v0v2.dotProduct(qvec)* invDet;

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