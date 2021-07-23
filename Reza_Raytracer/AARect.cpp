#include "AARect.h"

#include "GlobalParameters.h"

// github.com/RayTracing/raytracing.github.io/blob/master/src/TheNextWeek/aarect.h
// www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-box-intersection

bool XZRect::Hit(const Ray3& r,
    double t_min,
    double t_max, HitRecord& rec) const
{
    // r.Origin.y + t r.Direction.y = y
    // t = (y - r.Origin.y) / r.Direction.y
    auto t = (y - r.Origin().y()) / r.Direction().y();

    if (t < t_min || t > t_max)
    {
        return false;
    }

    auto x = r.Origin().x() + t * r.Direction().x();
    auto z = r.Origin().z() + t * r.Direction().z();

    if (x < x0 || x > x1 || z < z0 || z > z1)
    {
        return false;
    }

    rec.u = (x - x0) / (x1 - x0);
    rec.v = (z - z0) / (z1 - z0);
    rec.t = t;
    auto outward_normal = Vec3(0, 1, 0);
    rec.SetFaceNormal(r, outward_normal);
    rec.mat_ptr = material_ptr.get();
    rec.p = r.At(t);

    return true;
}

bool XZRect::BoundingBox(AABB& output_box) const
{
    output_box = AABB(Point3(x0, y - GlobalParameters::thin_padding, z0), 
                      Point3(x1, y + GlobalParameters::thin_padding, z1));
    return true;
}