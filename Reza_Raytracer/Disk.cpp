
#include "Disk.h"
#include "Sphere.h"
#include "GlobalParameters.h"

bool Disk::IntersectPlane(const Ray3& ray, double& t) const
{
    // assuming vectors are all normalized
    float denom = Dot(normal, ray.Direction());
    if (denom > 1e-6) 
    {
        auto ray_to_center = center - ray.Origin();
        t = Dot(ray_to_center, normal) / denom;
        return (t >= 0);
    }

    return false;
}

bool Disk::Hit(const Ray3& r,
    double t_min,
    double t_max, HitRecord& rec) const
{
    if (!IntersectPlane(r, rec.t))
    {
        return false;
    }

    rec.p = r.Origin() + r.Direction() * rec.t;
    Vec3 p_to_center = rec.p - center;
    double mag_sq = Dot(p_to_center, p_to_center);

    if (mag_sq > radius_squared)
    {
        return false;
    }

    rec.SetFaceNormal(r, normal);

    // TODO: calculate uv
    //rec.u =
    //rec.v =

    // raw pointer
    rec.mat_ptr = material_ptr.get();

    return true;
}

bool Disk::BoundingBox(AABB& output_box) const
{
    /*Vec3 padding(GlobalParameters::thin_padding);

    Vec3 min(fmin(v0.x(), fmin(v1.x(), v2.x())),
        fmin(v0.y(), fmin(v1.y(), v2.y())),
        fmin(v0.z(), fmin(v1.z(), v2.z())));

    min = min - padding;

    Vec3 max(fmax(v0.x(), fmax(v1.x(), v2.x())),
        fmax(v0.y(), fmax(v1.y(), v2.y())),
        fmax(v0.z(), fmax(v1.z(), v2.z())));

    max = max + padding;

    output_box = AABB(min, max);*/

    return true;
}