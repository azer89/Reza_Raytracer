#ifndef __SPHERE_H__
#define __SPHERE_H__

#include "Hittable.h"
#include "Material.h"

class Sphere : public Hittable
{
public:

    // Constructor 
	Sphere(Point3 cen, double r, shared_ptr<Material>& m)
    {
        center = cen;
        radius = r;
        
        // Copy shared_ptr 
        material_ptr = m;
    }

    virtual bool Hit(const Ray3& r, 
					 double t_min, 
					 double t_max, 
					 HitRecord& rec) const override;

    virtual bool BoundingBox(AABB& output_box) const override;

public:
    Point3 center;
    double radius;
    shared_ptr<Material> material_ptr;
};

#endif