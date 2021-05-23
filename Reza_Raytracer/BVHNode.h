
#ifndef __BVH_NODE_H__
#define __BVH_NODE_H__

//#include "Vec3.h"
//#include "Ray3.h"

#include "Hittable.h"
//#include "HittableList.h"

#include <iostream>


class BVHNode : public Hittable 
{
private:
    // only the leaf that has an actual object,
    // other else is BVHNode
    shared_ptr<Hittable> left_node;
    shared_ptr<Hittable> right_node;

public:
    AABB node_box;

public:
    //BVHNode();

    BVHNode(std::vector<shared_ptr<Hittable>>& src_objects)
        : BVHNode(src_objects, 0, src_objects.size())
    {
    }

    BVHNode(std::vector<shared_ptr<Hittable>>& src_objects,
            size_t start,
            size_t end);

    

    virtual bool Hit(const Ray3& r, double t_min, double t_max, HitRecord& rec) const override;

    virtual bool BoundingBox(AABB& output_box) const override;

    // original constructor
    /*
    BVHNode(const std::vector<shared_ptr<Hittable>>& src_objects,
                size_t start,
                size_t end);*/


};

inline bool BoxCompare(const shared_ptr<Hittable>& a, const shared_ptr<Hittable>& b, int axis)
{
    AABB box_a;
    AABB box_b;

    if (!a->BoundingBox(box_a) || !b->BoundingBox(box_b))
    {
        std::cerr << "No bounding box in bvh_node constructor.\n";
    }

    return box_a.Min().e[axis] < box_b.Min().e[axis];
}


inline bool BoxXCompare(const shared_ptr<Hittable>& a, const shared_ptr<Hittable>& b)
{
    return BoxCompare(a, b, 0);
}

inline bool BoxYCompare(const shared_ptr<Hittable>& a, const shared_ptr<Hittable>& b)
{
    return BoxCompare(a, b, 1);
}

inline bool BoxZCompare(const shared_ptr<Hittable>& a, const shared_ptr<Hittable>& b)
{
    return BoxCompare(a, b, 2);
}

#endif