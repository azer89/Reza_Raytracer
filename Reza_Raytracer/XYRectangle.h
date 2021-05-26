#ifndef __XY_RECTANGLE_H__
#define __XY_RECTANGLE_H__

#include "Hittable.h"
#include "Vec3.h"

#include "Material.h"

class XYRectangle : public Hittable
{
public:

    XYRectangle(double _x0, 
				double _x1, 
				double _y0, 
				double _y1, 
				double _k, 
				shared_ptr<Material> mat)
        : x0(_x0), x1(_x1), y0(_y0), y1(_y1), k(_k)
    {
        // stackoverflow.com/questions/41871115/why-would-i-stdmove-an-stdshared-ptr
        // why do I move a shared_ptr?
        this->mp = std::move(mat);
    };

    virtual bool Hit(const Ray3& r, double t_min, double t_max, HitRecord& rec) const override;

    virtual bool BoundingBox(AABB& output_box) const override;

public:
    shared_ptr<Material> mp;
    double x0, x1, y0, y1, k;
};

#endif



