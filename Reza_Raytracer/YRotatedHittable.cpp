#include "YRotatedHittable.h"

YRotatedHittable::YRotatedHittable(shared_ptr<Hittable> obj, double angle) : hittable_ptr(obj)
{
    auto radians = UsefulFunct::DegreesToRadians(angle);
    sin_theta = sin(radians);
    cos_theta = cos(radians);

    has_box = hittable_ptr->BoundingBox(bbox);

    Point3 min(UsefulConst::infinity, UsefulConst::infinity, UsefulConst::infinity);
    Point3 max(-UsefulConst::infinity, -UsefulConst::infinity, -UsefulConst::infinity);
}

bool YRotatedHittable::Hit(const Ray3& r, double t_min, double t_max, HitRecord& rec) const
{

}

bool YRotatedHittable::BoundingBox(AABB& output_box) const
{

}