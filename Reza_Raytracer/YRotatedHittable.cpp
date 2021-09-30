#include "YRotatedHittable.h"

YRotatedHittable::YRotatedHittable(shared_ptr<Hittable> obj, double angle)
{
    auto radians = UsefulFunctions::DegreesToRadians(angle);
    sin_theta = sin(radians);
    cos_theta = cos(radians);
}

bool YRotatedHittable::Hit(const Ray3& r, double t_min, double t_max, HitRecord& rec) const
{

}

bool YRotatedHittable::BoundingBox(AABB& output_box) const
{

}