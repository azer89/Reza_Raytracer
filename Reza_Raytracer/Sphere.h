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

    bool Hit(const Ray3& r,
        double t_min,
        double t_max,
        HitRecord& rec) const override;

    bool BoundingBox(AABB& output_box) const override;

private:
    // TODO refactor to return a Vec2
    static void GetSphereUV(const Point3& p, double& u, double& v);

public:
    double radius;
    Point3 center;
    shared_ptr<Material> material_ptr;
};

#endif