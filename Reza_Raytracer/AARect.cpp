#include "AARect.h"

#include "GlobalParameters.h"

/*
    Axis aligned rectangles
*/

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

bool XYRect::Hit(const Ray3& r,
                 double t_min,
                 double t_max, HitRecord& rec) const
{
    auto t = (z - r.Origin().z()) / r.Direction().z();

    if (t < t_min || t > t_max)
    {
        return false;
    }

    auto x = r.Origin().x() + t * r.Direction().x();
    auto y = r.Origin().y() + t * r.Direction().y();

    if (x < x0 || x > x1 || y < y0 || y > y1)
    {
        return false;
    }

    rec.u = (x - x0) / (x1 - x0);
    rec.v = (y - y0) / (y1 - y0);
    rec.t = t;
    auto outward_normal = Vec3(0, 0, 1);
    rec.SetFaceNormal(r, outward_normal);
    rec.mat_ptr = material_ptr.get();
    rec.p = r.At(t);

    return true;
}

bool YZRect::Hit(const Ray3& r,
                 double t_min,
                 double t_max, HitRecord& rec) const
{
    auto t = (x - r.Origin().x()) / r.Direction().x();
    if (t < t_min || t > t_max)
    {
        return false;
    }

    auto y = r.Origin().y() + t * r.Direction().y();
    auto z = r.Origin().z() + t * r.Direction().z();
    if (y < y0 || y > y1 || z < z0 || z > z1)
    {
        return false;
    }

    rec.u = (y - y0) / (y1 - y0);
    rec.v = (z - z0) / (z1 - z0);
    rec.t = t;
    auto outward_normal = Vec3(1, 0, 0);
    rec.SetFaceNormal(r, outward_normal);
    rec.mat_ptr = material_ptr.get();
    rec.p = r.At(t);

    return true;
}

bool XYRect::BoundingBox(AABB& output_box) const
{
    // The bounding box must have non-zero width in each dimension, 
    // so pad the Z dimension a small amount.
    output_box = AABB(Point3(x0, y0, z - GlobalParameters::thin_padding),
                      Point3(x1, y1, z + GlobalParameters::thin_padding));
    return true;
}

bool XZRect::BoundingBox(AABB& output_box) const
{
    // The bounding box must have non-zero width in each dimension, 
    // so pad the Y dimension a small amount.
    output_box = AABB(Point3(x0, y - GlobalParameters::thin_padding, z0), 
                      Point3(x1, y + GlobalParameters::thin_padding, z1));
    return true;
}

bool YZRect::BoundingBox(AABB& output_box) const
{
    // The bounding box must have non-zero width in each dimension, 
    // so pad the X dimension a small amount.
    output_box = AABB(Point3(x - GlobalParameters::thin_padding, y0, z0),
                      Point3(x + GlobalParameters::thin_padding, y1, z1));
    return true;
}