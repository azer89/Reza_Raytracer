#ifndef __TRIANGLE_H__
#define __TRIANGLE_H__

#include "Hittable.h"
#include "Material.h"

class Triangle : public Hittable
{
public:
    Triangle()
    {
    }

    Triangle(Vec3 _v0,
		     Vec3 _v1,
		     Vec3 _v2,
             shared_ptr<Material>& mat)
        : v0(_v0), 
          v1(_v1), 
          v2(_v2)
    {
        // Copy shared_ptr
        this->material_ptr = mat;
    };

    virtual bool Hit(const Ray3& r, double t_min, double t_max, HitRecord& rec) const override;

    virtual bool BoundingBox(AABB& output_box) const override;

public:
    shared_ptr<Material> material_ptr;
    Vec3 v0;
    Vec3 v1;
    Vec3 v2;
};

#endif



