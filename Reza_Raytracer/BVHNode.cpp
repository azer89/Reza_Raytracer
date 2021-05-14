
#include <algorithm>

#include "BVHNode.h"



BVHNode::BVHNode(const std::vector<shared_ptr<Hittable>>& src_objects, size_t start, size_t end) 
{
    auto objects = src_objects; // Create a modifiable array of the source scene objects

    // comparator is just a ternary operator
    // the type is bool (*comparator)(shared_ptr<Hittable> a, shared_ptr<Hittable> b)
    int axis = RandomInt(0, 2);
    auto comparator = (axis == 0) ? BoxXCompare
                    : (axis == 1) ? BoxYCompare
                                  : BoxZCompare;

    size_t object_span = end - start;

    if (object_span == 1) 
    {
        left = right = objects[start];
    }
    else if (object_span == 2) 
    {
        if (comparator(objects[start], objects[start + 1]) ) 
        {
            left = objects[start];
            right = objects[start + 1];
        }
        else 
        {
            left = objects[start + 1];
            right = objects[start];
        }
    }
    else 
    {
        std::sort(objects.begin() + start, objects.begin() + end, comparator);

        auto mid = start + object_span / 2;
        left = make_shared<BVHNode>(objects, start, mid);
        right = make_shared<BVHNode>(objects, mid, end);
    }

    AABB box_left;
    AABB box_right;

    if (!left->BoundingBox(box_left) || !right->BoundingBox(box_right) )
    {
        std::cerr << "No bounding box in bvh_node constructor.\n";
    }

    box = SurroundingBox(box_left, box_right);
}

bool BVHNode::Hit(const Ray3& r, double t_min, double t_max, HitRecord& rec) const
{
    if (!box.Hit(r, t_min, t_max))
    {
        return false;
    }

    // recursive
    bool hit_left = left->Hit(r, t_min, t_max, rec);
    bool hit_right = right->Hit(r, t_min, hit_left ? rec.t : t_max, rec);

    return hit_left || hit_right;
}
