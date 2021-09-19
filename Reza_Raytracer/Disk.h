#ifndef __DISK_H__
#define __DISK_H__

#include "Hittable.h"
#include "Material.h"

class Disk : public Hittable
{
public:
    Disk(Point3 cen, Vec3 n, double r, shared_ptr<Material>& m)
    {
        center = cen;
        normal = n;
        radius = r;
        radius_squared = radius * radius;

        // Copy shared_ptr 
        material_ptr = m;
    }


    bool Hit(const Ray3& r,
        double t_min,
        double t_max,
        HitRecord& rec) const override;

    bool BoundingBox(AABB& output_box) const override;

private:
    bool IntersectPlane(const Ray3& ray, double& t) const;

public:
    Point3 center;
    Vec3 normal;
    double radius;
    double radius_squared;
    shared_ptr<Material> material_ptr;
};

#endif