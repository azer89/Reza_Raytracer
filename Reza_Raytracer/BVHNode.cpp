
#include "BVHNode.h"

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