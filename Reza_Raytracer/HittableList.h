#ifndef __HITTABLE_LIST_H__
#define __HITTABLE_LIST_H__

#include "Hittable.h"

#include <memory>
#include <vector>

using std::unique_ptr;
using std::shared_ptr;
using std::vector;

class BVHNode;

class HittableList : public Hittable
{
public:
    HittableList()
    {	    
    }

    void Clear() { objects.clear(); }

    void CreateWorld();

    virtual bool Hit(const Ray3& r, 
					 double t_min, 
					 double t_max, 
					 HitRecord& rec) const override;

    virtual bool BoundingBox(AABB& output_box) const override;

public:
    shared_ptr<BVHNode> bvhRoot;

    vector<shared_ptr<Hittable>> objects;
};

#endif