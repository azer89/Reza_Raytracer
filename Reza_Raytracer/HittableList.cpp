
#include "HittableList.h"

#include "Sphere.h"
#include "XYRectangle.h"
#include "Triangle.h"
#include "FileReader.h"
//#include "BVHNode.h"

#include <string>

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
    //auto material_light = make_shared<DiffuseLight>(Color(0.6, 0.7, 0.6));
    auto material_ground = make_shared<Lambertian>(Color(0.6, 0.7, 0.6));
    auto material_center = make_shared<Lambertian>(Color(0.3, 0.3, 0.7));
	
    /*objects.push_back(make_shared<Sphere>(Point3(0, 0, -1),    0.5, material_center) );
      objects.push_back(make_shared<Sphere>(Point3(-1.1, 0, -1), 0.5, material_center) );
      objects.push_back(make_shared<Sphere>(Point3(1.1, 0, -1),  0.5, material_center) );
    //objects.push_back(make_shared<Sphere>(Point3(0, 0, -1),    2.5, material_center) );*/
    //objects.push_back(make_shared<Sphere>(Point3(0, -100, -1), 100, material_ground) );
        
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

    FileReader f_reader;
    /*const std::string filename = "C://Users//azer//workspace//Reza_Raytracer//objs//torus.obj";
    double scale = 0.75;
    Point3 offset(0, 0.3, -1);*/

    const std::string filename = "C://Users//azer//workspace//Reza_Raytracer//objs//stanford_bunny.obj";
    double scale = 0.75;
    Point3 offset(0, -0.73, -0.7);
    /*const std::string filename = "C://Users//azer//workspace//Reza_Raytracer//objs//suzanne.obj";
    double scale = 0.75;
    Point3 offset(0, -0.73, -0.7);*/
    /*
    lookfrom = Point3(0, 0, 2.3);
    lookat = Point3(0, 0, -1);
    vup = Vec3(0, 1, 0);
    */

    std::cout << "read obj file " << filename << '\n';
    f_reader.ReadOBJ(filename, vertices, faces);
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
    }
    std::cout << "done reading\n\n";

    // init BVH
    bvhRoot = make_shared<BVHNode>(objects);
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

