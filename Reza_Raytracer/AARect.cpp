#include "AARect.h"

#include "GlobalParameters.h"

bool XZRect::Hit(const Ray3& r,
    double t_min,
    double t_max, HitRecord& rec) const
{

    return true;
}

bool XZRect::BoundingBox(AABB& output_box) const
{
    output_box = AABB(Point3(x0, y - GlobalParameters::thin_padding, z0), 
                      Point3(x1, y + GlobalParameters::thin_padding, z1));
    return true;
}