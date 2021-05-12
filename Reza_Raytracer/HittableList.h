#ifndef __HITTABLE_LIST_H__
#define __HITTABLE_LIST_H__

#include "Hittable.h"

#include <memory>
#include <vector>

using std::unique_ptr;
using std::shared_ptr;
using std::vector;

class HittableList : public Hittable
{
public:
    HittableList()
    {	    
    }

    /*HittableList(const shared_ptr<Hittable>& object)
    {
	    Add(object);
    }*/

    void Clear() { objects.clear(); }

    /*void Add(const shared_ptr<Hittable>& object)
    {
	    objects.push_back(object);
    }*/

    void CreateWorld();

    virtual bool Hit(const Ray3& r, 
					 double t_min, 
					 double t_max, 
					 HitRecord& rec) const override;

    virtual bool BoundingBox(AABB& output_box) const override;

public:
    vector<shared_ptr<Hittable>> objects;
    //vector<unique_ptr<Hittable>> objects;
};

#endif