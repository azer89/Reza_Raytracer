#ifndef __HIT_RECORD_H__
#define __HIT_RECORD_H__

#include "Vec3.h"
#include "Ray3.h"

class Material;

struct HitRecord
{
public:
    // Hit point
    Point3 p;

    // Hit normal
    Vec3 normal;

    // Hit material
    Material* mat_ptr;

    // origin + t * direction
    double t;

    // TODO: change to Vec2
    double u;
    double v;

    bool front_face;

public:
    HitRecord()
    {
        mat_ptr = nullptr;
        t = 0; 
        u = 0;
        v = 0;
        front_face = false;
    }

    // Make sure the normal always against the ray 
    inline void SetFaceNormal(const Ray3& r, const Vec3& outward_normal)
    {
        front_face = Dot(r.Direction(), outward_normal) < 0;
        normal = front_face ? outward_normal : -outward_normal;
    }
};

#endif