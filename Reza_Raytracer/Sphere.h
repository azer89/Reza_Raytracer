#ifndef __SPHERE_H__
#define __SPHERE_H__

#include "Hittable.h"
#include "Vec3.h"

class Sphere : public Hittable
{
public:
    Sphere()
    {	    
    }

	Sphere(Point3 cen, double r) : center(cen), radius(r)
    {	    
    }

    virtual bool Hit(const Ray3& r, 
					 double t_min, 
					 double t_max, 
					 HitRecord& rec) const override;

public:
    Point3 center;
    double radius;
};

#endif