
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
    XMLParser::LoadMaterials(mat_map);

    auto material_ground = make_shared<Lambertian>(Color(0.6, 0.7, 0.6));

    auto material_side = make_shared<Metal>(Color(0.7, 0.3, 0.3));
    auto material_center = make_shared<Lambertian>(Color(0.3, 0.3, 0.7));
	
    objects.push_back(make_shared<Sphere>(Point3(0, 0, -1),    0.5, material_center) );
    objects.push_back(make_shared<Sphere>(Point3(-1.1, 0, -1), 0.5, material_side) );
    objects.push_back(make_shared<Sphere>(Point3(1.1, 0, -1),  0.5, material_side) );

    objects.push_back(make_shared<Sphere>(Point3(0, -100.5, -1), 100, material_ground) );

        
    /*objects.push_back(make_shared<Triangle>(Point3( 0, 0.25,  0),
											Point3( 1, 0.25, -1),
										    Point3(-1, 0.25, -1),        
										    material_center));

    objects.push_back(make_shared<Triangle>(Point3(   0,  0,  -0.5),
										    Point3( 0.5, 0.5, -0.5),
										    Point3(-0.5, 0.5, -0.5),
										    material_center));
    */

    // Load triangle mesh
    std::vector<Vec3> vertices;
    std::vector< std::vector<int>> faces;

    OBJReader obj_reader;
    const std::string filename = "C://Users//azer//workspace//Reza_Raytracer//objs//stanford_bunny.obj";
    double scale = 0.75;
    Point3 offset(0, -0.7, -0.7);    
    /*obj_reader.ReadOBJ(filename, vertices, faces);
    for (int i = 0; i < faces.size(); i++)
    {
        int i1 = faces[i][0];
        int i2 = faces[i][1];
        int i3 = faces[i][2];

        Point3 p1 = vertices[i1] * scale + offset;
        Point3 p2 = vertices[i2] * scale + offset;
        Point3 p3 = vertices[i3] * scale + offset;

        objects.push_back(make_shared<Triangle>(p1,
                                                p2,
                                                p3,
                                                material_center));
    }*/
    

    // init BVH
    std::cout << "Building BVH\n";
    auto start1 = std::chrono::steady_clock::now();
    bvhRoot = make_shared<BVHNode>(objects);
    auto end1 = std::chrono::steady_clock::now();
    std::cout << "BVH done in " << std::chrono::duration_cast<std::chrono::milliseconds>(end1 - start1).count() << " ms\n\n";
    //std::cout << "BVH done\n\n";
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

