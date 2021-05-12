#ifndef __BVH_H__
#define __BVH_H__

#include "Vec3.h"
#include "Ray3.h"

#include "Hittable.h"
#include "HittableList.h"


class BVHNode : public Hittable 
{
public:
    BVHNode();

    BVHNode(const HittableList& list)
        : BVHNode(list.objects, 0, list.objects.size())
    {
    }

    BVHNode(const std::vector<shared_ptr<Hittable>>& src_objects, 
            size_t start, 
            size_t end);

    virtual bool Hit( const Ray3& r, double t_min, double t_max, HitRecord& rec) const override;

    virtual bool BoundingBox(AABB& output_box) const override;

public:
    shared_ptr<Hittable> left;
    shared_ptr<Hittable> right;
    AABB box;
};

bool BVHNode::BoundingBox(AABB& output_box) const 
{
    output_box = box;
    return true;
}

#endif