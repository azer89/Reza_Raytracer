#ifndef __TRIANGLE_H__
#define __TRIANGLE_H__

#include "Hittable.h"
#include "Material.h"
#include "Vec2.h"

class Triangle : public Hittable
{
public:
    // Constructor #1
    Triangle(Vec3 _v0,
		     Vec3 _v1,
		     Vec3 _v2,
             shared_ptr<Material>& mat)
        : v0(_v0), 
          v1(_v1), 
          v2(_v2)
    {
        // Copy shared_ptr
        this->material_ptr = mat;

        this->v0v1 = v1 - v0;
        this->v0v2 = v2 - v0;
        auto normal = Cross(v0v1, v0v2);

        this->n0 = normal;
        this->n1 = normal;
        this->n2 = normal;

        this->uv0 = Vec2(0, 0);
        this->uv1 = Vec2(0, 0);
        this->uv2 = Vec2(0, 0);
    };

    // Constructor #2
    Triangle(Vec3 _v0,
		     Vec3 _v1,
		     Vec3 _v2,
             Vec3 _n0,
		     Vec3 _n1,
		     Vec3 _n2,
             shared_ptr<Material>& mat)
        : v0(_v0), 
          v1(_v1), 
          v2(_v2),
          n0(_n0),
          n1(_n1),
          n2(_n2)
    {
        // Copy shared_ptr
        this->material_ptr = mat;

        this->v0v1 = v1 - v0;
        this->v0v2 = v2 - v0;

        this->uv0 = Vec2(0, 0);
        this->uv1 = Vec2(0, 0);
        this->uv2 = Vec2(0, 0);
    };

    // Oh man I have too many costructors
    Triangle(Vec3 _v0,
		     Vec3 _v1,
		     Vec3 _v2,
             Vec3 _n0,
		     Vec3 _n1,
		     Vec3 _n2,
             Vec2 _uv0,
             Vec2 _uv1,
             Vec2 _uv2,
             shared_ptr<Material>& mat)
        : v0(_v0), 
          v1(_v1), 
          v2(_v2),
          n0(_n0),
          n1(_n1),
          n2(_n2),
          uv0(_uv0),
          uv1(_uv1),
          uv2(_uv2)
    {
        // Copy shared_ptr
        this->material_ptr = mat;

        this->v0v1 = v1 - v0;
        this->v0v2 = v2 - v0;

        this->uv0 = Vec2(0, 0);
        this->uv1 = Vec2(0, 0);
        this->uv2 = Vec2(0, 0);
    };

    virtual bool Hit(const Ray3& r, double t_min, double t_max, HitRecord& rec) const override;

    virtual bool BoundingBox(AABB& output_box) const override;

private:
    Vec2 GetTriangleUV(double u, double v, double w) const;

public:
    // Material
    shared_ptr<Material> material_ptr;
    
    // Triangle axes
    Vec3 v0v1;
    Vec3 v0v2;

    // Vertex positions
    Vec3 v0;
    Vec3 v1;
    Vec3 v2;
    
    // Vertex normals
    Vec3 n0;
    Vec3 n1;
    Vec3 n2;

    // UV coordinates
    Vec2 uv0;
    Vec2 uv1;
    Vec2 uv2;
};

#endif



