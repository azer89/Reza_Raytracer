#ifndef __SPHERE_H__
#define __SPHERE_H__

#include "Hittable.h"
#include "Vec3.h"
#include "Material.h"

class Sphere : public Hittable
{
public:
    Sphere()
    {	    
    }

	// shared_ptr is passed by value 
	Sphere(Point3 cen, double r, shared_ptr<Material> m)
    {
        center = cen;
        radius = r;

    	// stackoverflow.com/questions/41871115/why-would-i-stdmove-an-stdshared-ptr
    	// why do I move a shared_ptr?
        mat_ptr = std::move(m);
    }

    virtual bool Hit(const Ray3& r, 
					 double t_min, 
					 double t_max, 
					 HitRecord& rec) const override;

    virtual bool BoundingBox(AABB& output_box) const override;

public:
    Point3 center;
    double radius;
    shared_ptr<Material> mat_ptr;
};

#endif