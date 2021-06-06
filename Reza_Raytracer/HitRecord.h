#ifndef __HIT_RECORD_H__
#define __HIT_RECORD_H__

#include "Vec3.h"
#include "Ray3.h"

class Material;

struct HitRecord
{
    Point3 p;
    Vec3 normal;

    Material* mat_ptr;

    // origin + t * direction
    double t;

    bool front_face;

    // Texture
    double u;
    double v;

    // Make sure the normal always against the ray 
    inline void SetFaceNormal(const Ray3& r, const Vec3& outward_normal)
    {
        front_face = Dot(r.Direction(), outward_normal) < 0;
        normal = front_face ? outward_normal : -outward_normal;
    }
};

#endif