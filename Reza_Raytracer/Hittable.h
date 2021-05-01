#ifndef HITTABLE_H
#define HITTABLE_H

#include "Ray3.h"

struct HitRecord
{
    Point3 p;
    Vec3 normal;
    double t;
    bool front_face;

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
};

#endif
