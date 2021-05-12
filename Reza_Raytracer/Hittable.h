#ifndef HITTABLE_H
#define HITTABLE_H

#include "Ray3.h"
#include "AABB.h"

class Material;

struct HitRecord
{
    Point3 p;
    Vec3 normal;
    shared_ptr<Material> mat_ptr;
    double t;
    bool front_face;

	// texture
    double u;
    double v;

	// make sure the normal always against the ray 
    inline void SetFaceNormal(const Ray3& r, const Vec3& outward_normal)
	{
        front_face = Dot(r.Direction(), outward_normal) < 0;
        normal = front_face ? outward_normal : -outward_normal;
    }
};

class Hittable
{
public:
    virtual bool Hit(const Ray3& r, double t_min, double t_max, HitRecord& rec) const = 0;
    virtual bool BoundingBox(AABB& output_box) const = 0;
};

#endif
