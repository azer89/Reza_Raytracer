#include "BVHNode.h"
#include "Triangle.h"

#include <algorithm>

// Improved constructor without random
// github.com/RayTracing/TheRestOfYourLife/blob/master/src/bvh.h
BVHNode::BVHNode(std::vector<shared_ptr<Hittable>>& src_objects, 
                 size_t start, 
                 size_t end)
{
    // Assign first object's BB to box
    src_objects[start]->BoundingBox(node_box);
    AABB dummy_box;
    for (size_t i = start + 1; i < end; i++)
    {
        bool has_bb = src_objects[i]->BoundingBox(dummy_box);
        if (!has_bb)
        {
            std::cerr << "No bounding box in bvh_node constructor.\n";
        }

        // Update box
        node_box = SurroundingBox(node_box, dummy_box);
    }

    // It seems that in order to make the splitting work,
    // the AABBs for thin objects should be padded 
    int axis = node_box.LongestAxis();
    auto comparator = [axis](const shared_ptr<Hittable>& a, 
                             const shared_ptr<Hittable>& b)
    {
        return (axis == 0) ? BoxXCompare(a, b)
             : (axis == 1) ? BoxYCompare(a, b)
                           : BoxZCompare(a, b);
    };

    size_t object_span = end - start;

    // Creating a tree
    if (object_span == 1)
    {
        // Option 1: Pointing to the same object
        left_node = right_node = src_objects[start];

        // Option 2: github.com/RayTracing/raytracing.github.io/issues/804
        //left_node = src_objects[start];
        //right_node = empty_object;
    }
    else if (object_span == 2)
    {
        if (comparator(src_objects[start], src_objects[start + 1]))
        {
            left_node  = src_objects[start];
            right_node = src_objects[start + 1];
        }
        else
        {
            left_node  = src_objects[start + 1];
            right_node = src_objects[start];
        }
    }
    else if (object_span == 3)
    {
        // Binary partitioning
        std::sort(src_objects.begin() + start, src_objects.begin() + end, comparator);

        left_node = src_objects[start];
        right_node = make_shared<BVHNode>(src_objects, start + 1, end);
    }
    else
    {
        // Binary partitioning
        std::sort(src_objects.begin() + start, src_objects.begin() + end, comparator);

        auto mid = start + object_span / 2;
        left_node  = make_shared<BVHNode>(src_objects, start, mid);
        right_node = make_shared<BVHNode>(src_objects, mid, end);
    }
}

bool BVHNode::Hit(const Ray3& r, double t_min, double t_max, HitRecord& rec) const
{    
    if (!node_box.Hit(r, t_min, t_max))
    {
        return false;
    }

    // Recursive
    bool hit_left  = left_node->Hit( r, t_min, t_max,                    rec);
    bool hit_right = right_node->Hit(r, t_min, hit_left ? rec.t : t_max, rec);

    return hit_left || hit_right;
}

bool BVHNode::BoundingBox(AABB& output_box) const
{
    output_box = node_box;
    return true;
}