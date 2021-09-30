#ifndef __Y_ROTATED_HITTABLE_H__
#define __Y_ROTATED_HITTABLE_H__

#include "HitRecord.h"
#include "Ray3.h"
#include "AABB.h"
#include "Hittable.h"

class Material;

class YRotatedHittable : Hittable
{
public:
    YRotatedHittable(shared_ptr<Hittable> obj, double angle);

    virtual bool Hit(const Ray3& r, double t_min, double t_max, HitRecord& rec) const override;

    virtual bool BoundingBox(AABB& output_box) const override;

public:
    double sin_theta;
    double cos_theta;
};
#endif
