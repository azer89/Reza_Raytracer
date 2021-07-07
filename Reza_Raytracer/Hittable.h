#ifndef __HITTABLE_H__
#define __HITTABLE_H__

#include "HitRecord.h"
#include "Ray3.h"
#include "AABB.h"

class Material;

class Hittable
{
public:
    virtual bool Hit(const Ray3& r, double t_min, double t_max, HitRecord& rec) const = 0;
    virtual bool BoundingBox(AABB& output_box) const = 0;
};

class NullHittable : Hittable
{
public:
    bool Hit(const Ray3& r, double t_min, double t_max, HitRecord& rec) const override
    {
        return false;
    }

    bool BoundingBox(AABB& output_box) const override
    {
        output_box = AABB();
        return true;
    }
};

#endif
