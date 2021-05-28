
#include "HittableList.h"

#include "Sphere.h"
#include "XYRectangle.h"
#include "Triangle.h"
#include "OBJReader.h"

#include "XMLParser.h"
#include "BVHNode.h"

#include <string>
#include <chrono>
#include <unordered_map>

using std::make_unique;

bool HittableList::Hit(const Ray3& r, 
					   double t_min, 
					   double t_max, 
                       HitRecord& rec) const
{
    

    // BVH version
    bool hit_anything = bvhRoot->Hit(r, t_min, t_max, rec);

    // Brute force version
    /*HitRecord temp_rec;
    bool hit_anything = false;
    auto closest_so_far = t_max; // very clever!

    for (const auto& object : objects) 
    {
        if (object->Hit(r, t_min, closest_so_far, temp_rec)) 
        {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }*/

    return hit_anything;
}

void HittableList::CreateWorld()
{
    std::unordered_map<std::string, shared_ptr<Material>> mat_map;
    XMLParser::LoadMaterialsAndObjects(mat_map, objects);    

    // init BVH
    std::cout << "Building BVH\n";
    auto start1 = std::chrono::steady_clock::now();
    bvhRoot = make_shared<BVHNode>(objects);
    auto end1 = std::chrono::steady_clock::now();
    std::cout << "BVH done in " << std::chrono::duration_cast<std::chrono::milliseconds>(end1 - start1).count() << " ms\n\n";
}

bool HittableList::BoundingBox(AABB& output_box) const
{
    AABB temp_box;
    bool first_box = true;

    for (const auto& object : objects) 
    {
        if (!object->BoundingBox(temp_box))
        {
            return false;
        }

        output_box = first_box ? temp_box : SurroundingBox(output_box, temp_box);
        first_box = false;
    }

    return true;
}

