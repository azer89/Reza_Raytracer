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
    	// not good, compute the other root
        root = (-half_b + sqrtd) / a;
        if (root < t_min || t_max < root)
        {
            return false;
        }
    }

    rec.t = root;
    rec.p = r.At(rec.t);
    Vec3 outward_normal = (rec.p - center) / radius;
    rec.SetFaceNormal(r, outward_normal);
    GetSphereUV(outward_normal, rec.u, rec.v);

    // raw pointer
    rec.mat_ptr = material_ptr.get();
	
    return true;
}

bool Sphere::BoundingBox(AABB& output_box) const
{
    output_box = AABB(center - Vec3(radius, radius, radius),
					  center + Vec3(radius, radius, radius));
	
    return true;
}

void Sphere::GetSphereUV(const Point3& p, double& u, double& v)
{
    /*
    p: a given point on the sphere of radius one, centered at the origin.
    u: returned value [0,1] of angle around the Y axis from X=-1.
    v: returned value [0,1] of angle from Y=-1 to Y=+1.
        <1 0 0> yields <0.50 0.50>       <-1  0  0> yields <0.00 0.50>
        <0 1 0> yields <0.50 1.00>       < 0 -1  0> yields <0.50 0.00>
        <0 0 1> yields <0.25 0.50>       < 0  0 -1> yields <0.75 0.50>
    */

    auto theta = acos(-p.y());
    auto phi = atan2(-p.z(), p.x()) + UsefulConstants::pi;

    u = phi / (2 * UsefulConstants::pi);
    v = theta / UsefulConstants::pi;
}