
#ifndef __BVH_NODE_H__
#define __BVH_NODE_H__

//#include "Vec3.h"
//#include "Ray3.h"

#include "Hittable.h"
//#include "HittableList.h"

#include <iostream>


class BVHNode : public Hittable 
{
public:
    BVHNode();

    // cyclic dependency
    /*BVHNode(const HittableList& list)
        : BVHNode(list.objects, 0, list.objects.size())
    {
    }*/

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



inline bool BoxCompare(const shared_ptr<Hittable> a, const shared_ptr<Hittable> b, int axis) 
{
    AABB box_a;
    AABB box_b;

    if (!a->BoundingBox(box_a) || !b->BoundingBox(box_b))
    {
        std::cerr << "No bounding box in bvh_node constructor.\n";
    }

    return box_a.Min().e[axis] < box_b.Min().e[axis];
}


inline bool BoxXCompare(const shared_ptr<Hittable> a, const shared_ptr<Hittable> b)
{
    return BoxCompare(a, b, 0);
}

inline bool BoxYCompare(const shared_ptr<Hittable> a, const shared_ptr<Hittable> b)
{
    return BoxCompare(a, b, 1);
}

inline bool BoxZCompare(const shared_ptr<Hittable> a, const shared_ptr<Hittable> b)
{
    return BoxCompare(a, b, 2);
}

#endif