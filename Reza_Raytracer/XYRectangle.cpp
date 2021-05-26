

#include "XYRectangle.h"
#include <iostream>

bool XYRectangle::Hit(const Ray3& r, double t_min, double t_max, HitRecord& rec) const
{
    auto t = (k - r.Origin().z()) / r.Direction().z();
	
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

	// Hit Record
    rec.u = (x - x0) / (x1 - x0);
    rec.v = (y - y0) / (y1 - y0);

	rec.t = t;

	auto outward_normal = Vec3(0, 0, 1);
    rec.SetFaceNormal(r, outward_normal);
    rec.mat_ptr = mp;
    rec.p = r.At(t);
	
    return true;
}

bool XYRectangle::BoundingBox(AABB& output_box) const
{
    std::cerr << "not implemented\n";
    return false;
}


