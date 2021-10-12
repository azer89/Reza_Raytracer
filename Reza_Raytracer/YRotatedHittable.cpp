#include "YRotatedHittable.h"

YRotatedHittable::YRotatedHittable(shared_ptr<Hittable> obj, double angle) : hittable_ptr(obj)
{
    auto radians = UsefulFunct::DegreesToRadians(angle);
    sin_theta = sin(radians);
    cos_theta = cos(radians);

    has_box = hittable_ptr->BoundingBox(bbox);

    Point3 min(UsefulConst::infinity, UsefulConst::infinity, UsefulConst::infinity);
    Point3 max(-UsefulConst::infinity, -UsefulConst::infinity, -UsefulConst::infinity);

    for (int i = 0; i < 2; i++) 
    {
        for (int j = 0; j < 2; j++) 
        {
            for (int k = 0; k < 2; k++) 
            {
                auto x = i * bbox.Max().x() + (1 - i) * bbox.Min().x();
                auto y = j * bbox.Max().y() + (1 - j) * bbox.Min().y();
                auto z = k * bbox.Max().z() + (1 - k) * bbox.Min().z();

                auto newx = cos_theta * x + sin_theta * z;
                auto newz = -sin_theta * x + cos_theta * z;

                Vec3 tester(newx, y, newz);

                for (int c = 0; c < 3; c++) 
                {
                    min[c] = fmin(min[c], tester[c]);
                    max[c] = fmax(max[c], tester[c]);
                }
            }
        }
    }

    bbox = AABB(min, max);
}

bool YRotatedHittable::Hit(const Ray3& r, double t_min, double t_max, HitRecord& rec) const
{
    // Rotate origin
    auto origin = r.Origin();
    origin[0] = cos_theta * r.Origin()[0] - sin_theta * r.Origin()[2];
    origin[2] = sin_theta * r.Origin()[0] + cos_theta * r.Origin()[2];

    // Rotate direction
    auto direction = r.Direction();
    direction[0] = cos_theta * r.Direction()[0] - sin_theta * r.Direction()[2];
    direction[2] = sin_theta * r.Direction()[0] + cos_theta * r.Direction()[2];

    Ray3 rotated_ray(origin, direction);

    if (!hittable_ptr->Hit(rotated_ray, t_min, t_max, rec))
    {
        return false;
    }

    auto p = rec.p; // hit point
    auto normal = rec.normal; // hit normal

    p[0] = cos_theta * rec.p[0] + sin_theta * rec.p[2];
    p[2] = -sin_theta * rec.p[0] + cos_theta * rec.p[2];

    normal[0] = cos_theta * rec.normal[0] + sin_theta * rec.normal[2];
    normal[2] = -sin_theta * rec.normal[0] + cos_theta * rec.normal[2];

    rec.p = p;
    rec.SetFaceNormal(rotated_ray, normal);

    return true;
}

bool YRotatedHittable::BoundingBox(AABB& output_box) const
{
    output_box = bbox;
    return true;
}