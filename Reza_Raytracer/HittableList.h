#ifndef __HITTABLE_LIST_H__
#define __HITTABLE_LIST_H__

#include "Hittable.h"

#include <memory>
#include <vector>
#include <unordered_map>

using std::unique_ptr;
using std::shared_ptr;
using std::vector;

class BVHNode;
class Texture;

class HittableList : public Hittable
{
public:
    HittableList()
    {	    
    }

    void Clear() { objects.clear(); }

    void CreateWorld();

    virtual bool Hit(const Ray3& r, 
					 double t_min, 
					 double t_max, 
					 HitRecord& rec) const override;

    virtual bool BoundingBox(AABB& output_box) const override;

private:
    // Root of the BVH
    shared_ptr<BVHNode> bvh_root;

    // List of textures
    std::unordered_map<std::string, shared_ptr<Texture>> texture_map;

    // Materials, you need their names descibed in the main.xml
    std::unordered_map<std::string, shared_ptr<Material>> material_map;

    // List of objects
    vector<shared_ptr<Hittable>> objects;
};

#endif