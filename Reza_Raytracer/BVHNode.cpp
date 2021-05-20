
#include <algorithm>

#include "BVHNode.h"


// improved constructor without random
// github.com/RayTracing/TheRestOfYourLife/blob/master/src/bvh.h
BVHNode::BVHNode(std::vector<shared_ptr<Hittable>>& src_objects, 
                 size_t start, 
                 size_t end)
{
    // need to be optimized because we duplicate shared_ptrs
    //auto objects = src_objects; 

    // assign first object's BB to box
    src_objects[start]->BoundingBox(node_box);
    AABB dummy_box;
    for(int i = start + 1; i < end; i++)
    {
        bool has_bb = src_objects[i]->BoundingBox(dummy_box);
        if (!has_bb)
        {
            std::cerr << "No bounding box in bvh_node constructor.\n";
        }
        // update box
        node_box = SurroundingBox(node_box, dummy_box);
    }

    int axis = node_box.LongestAxis();
    auto comparator = (axis == 0) ? BoxXCompare
                    : (axis == 1) ? BoxYCompare
                                  : BoxZCompare;

    size_t object_span = end - start;

    // creating a tree
    if (object_span == 1)
    {
        // pointing to the same object
        left_node = right_node = src_objects[start];
        num_actual_object = 1;

        // debugging
        /*std::cout << "Single AABB area = " << node_box.Area() << 
            " Min = (" << node_box.Min()[0] << ", " << node_box.Min()[1] << ", " << node_box.Min()[2] << ")" <<
            " Max = (" << node_box.Max()[0] << ", " << node_box.Max()[1] << ", " << node_box.Max()[2] << ")" << '\n';
        */
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

        // debugging
        /*num_actual_object = 2;
        AABB left_box;
        left_node->BoundingBox(left_box);
        AABB right_box;
        right_node->BoundingBox(right_box);

        // debugging        
        std::cout << "Left AABB area = " << left_box.Area() <<
            " Min = (" << left_box.Min()[0] << ", " << left_box.Min()[1] << ", " << left_box.Min()[2] << ")" <<
            " Max = (" << left_box.Max()[0] << ", " << left_box.Max()[1] << ", " << left_box.Max()[2] << ")" << '\n';

        std::cout << "Right AABB area = " << right_box.Area() <<
            " Min = (" << right_box.Min()[0] << ", " << right_box.Min()[1] << ", " << right_box.Min()[2] << ")" <<
            " Max = (" << right_box.Max()[0] << ", " << right_box.Max()[1] << ", " << right_box.Max()[2] << ")" << '\n';
        */
    }
    else
    {
        // binary partitioning
        // we are sorting a vector of shared_ptrs, 
        // it's ugly code because we modify a resourse we don't own
        // but technically there's no problem
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

    // recursive
    bool hit_left  = left_node->Hit( r, t_min, t_max,                    rec);
    bool hit_right = right_node->Hit(r, t_min, hit_left ? rec.t : t_max, rec);

    return hit_left || hit_right;
}

bool BVHNode::BoundingBox(AABB& output_box) const
{
    output_box = node_box;
    return true;
}

// original constructor
/*void
BVHNode::BVHNode_Old(const std::vector<shared_ptr<Hittable>>& src_objects, size_t start, size_t end)
{
    // need to be optimized because we duplicate shared_ptrs
    auto objects = src_objects; // Create a modifiable array of the source scene objects

    // comparator is just a ternary operator
    // bool (*comparator)(shared_ptr<Hittable> a, shared_ptr<Hittable> b)
    int axis = RandomInt(0, 2); // can be replaced with the longest axis
    auto comparator = (axis == 0) ? BoxXCompare
                    : (axis == 1) ? BoxYCompare
                                  : BoxZCompare;

    size_t object_span = end - start;

    // creating a tree
    if (object_span == 1)
    {
        // pointing to the same object
        left_node = right_node = objects[start];
        num_actual_object = 1;
    }
    else if (object_span == 2)
    {
        if (comparator(objects[start], objects[start + 1]) )
        {
            left_node = objects[start];
            right_node = objects[start + 1];
        }
        else
        {
            left_node  = objects[start + 1];
            right_node = objects[start];
        }

        num_actual_object = 2;
    }
    else
    {
        // binary partitioning
        std::sort(objects.begin() + start, objects.begin() + end, comparator);

        auto mid = start + object_span / 2;
        left_node  = make_shared<BVHNode>(objects, start, mid);
        right_node = make_shared<BVHNode>(objects, mid, end);
    }

    AABB box_left;
    AABB box_right;

    if (!left_node->BoundingBox(box_left) || !right_node->BoundingBox(box_right) )
    {
        std::cerr << "No bounding box in bvh_node constructor.\n";
    }

    node_box = SurroundingBox(box_left, box_right);
}*/
