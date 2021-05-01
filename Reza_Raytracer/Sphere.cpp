
#include "Sphere.h"


bool Sphere::Hit(const Ray3& r, 
				 double t_min, 
				 double t_max, HitRecord& rec) const
{
    /*
    Equation
        b * b t^2 +
        2 b * (A - C) t +
        (A - C) * (A - C) - r^2
        = 0
    where
        t is a scalar
        b is a direction vector
        A is the the ray origin
        C is the center of the sphere
    */

    Vec3 oc = r.Origin() - center;
	
    // original version
    /*auto a = Dot(r.Direction(), r.Direction());
    auto b = 2.0 * Dot(oc, r.Direction());
    auto c = Dot(oc, oc) - radius * radius;
    auto discriminant = b * b - 4 * a * c;*/

	// improved version    
    auto a = r.Direction().LengthSquared();
    auto half_b = Dot(oc, r.Direction());
    auto c = oc.LengthSquared() - radius * radius;

    auto discriminant = half_b * half_b - a * c;
    if (discriminant < 0)
    {
        return false;
    }
    
    // original version
    //return (-b - sqrt(discriminant)) / (2.0 * a);
    
    // Find the nearest root that lies in the acceptable range.
    auto sqrtd = sqrt(discriminant);
    auto root = (-half_b - sqrtd) / a;
    if (root < t_min || t_max < root) 
    {
    	// not good, compute teh other root
        root = (-half_b + sqrtd) / a;
        if (root < t_min || t_max < root)
        {
            return false;
        }
    }

    rec.t = root;
    rec.p = r.At(rec.t);
    //rec.normal = (rec.p - center) / radius;
    Vec3 outward_normal = (rec.p - center) / radius;
    rec.SetFaceNormal(r, outward_normal);
	
    return true;
}