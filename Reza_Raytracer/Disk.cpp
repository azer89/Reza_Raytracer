
#include "Disk.h"
#include "Sphere.h"
#include "GlobalParameters.h"

// Get the value of t if the function returns true
bool Disk::IntersectPlane(const Ray3& ray, double& t) const
{
    // Assuming vectors are all normalized
    float denom = Dot(normal, ray.Direction());
    if (denom > 1e-6) 
    {
        auto ray_to_center = center - ray.Origin();
        t = Dot(ray_to_center, normal) / denom;
        return (t >= 0);
    }

    return false;
}

// TODO: There seem to be a rectangle artifact
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
    //rec.u = ?
    //rec.v = ?

    // raw pointer
    rec.mat_ptr = material_ptr.get();

    return true;
}

bool Disk::BoundingBox(AABB& output_box) const
{
    // www.gamedev.net/forums/topic/583417-disc-axis-aligned-bounding-box/
    // www.iquilezles.org/www/articles/diskbbox/diskbbox.htm
    auto e_x = radius * sqrt(1.0 - normal.x() * normal.x());
    auto e_y = radius * sqrt(1.0 - normal.y() * normal.y());
    auto e_z = radius * sqrt(1.0 - normal.z() * normal.z());
    Vec3 e(e_x, e_y, e_z);

    output_box = AABB(center - e, center + e);

    return true;
}