#ifndef __HITTABLE_LIST_H__
#define __HITTABLE_LIST_H__

#include "Hittable.h"

#include <memory>
#include <vector>

using std::shared_ptr;
using std::vector;

class HittableList : public Hittable
{
public:
    HittableList()
    {	    
    }

    HittableList(const shared_ptr<Hittable>& object)
    {
	    Add(object);
    }

    void Clear() { objects.clear(); }

    void Add(const shared_ptr<Hittable>& object)
    {
	    objects.push_back(object);
    }

    virtual bool Hit(const Ray3& r, 
					 double t_min, 
					 double t_max, 
					 HitRecord& rec) const override;

public:
    vector<shared_ptr<Hittable>> objects;
};

#endif