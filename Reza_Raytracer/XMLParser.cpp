#include "Vec3.h"
#include "XMLParser.h"
#include "GlobalParameters.h"
#include "OBJReader.h"
#include "tinyxml2.h"

#include "Hittable.h"
#include "Sphere.h"
#include "Triangle.h"
#include "Texture.h"
#include "Material.h"

#include <iostream>

// C://Users//azer//workspace//Reza_Raytracer//scenes//main.xml

using namespace tinyxml2;
using namespace std;

inline Vec3 GetVec3(const XMLElement* element)
{
    double x;
    double y;
    double z;

    element->QueryDoubleAttribute("x", &x);
    element->QueryDoubleAttribute("y", &y);
    element->QueryDoubleAttribute("z", &z);

    return Vec3(x, y, z);
}

inline Color GetColor(const XMLElement* element)
{
    double r;
    double g;
    double b;

    element->QueryDoubleAttribute("r", &r);
    element->QueryDoubleAttribute("g", &g);
    element->QueryDoubleAttribute("b", &b);

    return Color(r, g, b);
}

inline int GetInt(const XMLElement* element, string name = "value")
{
    int i;
    element->QueryIntAttribute(name.c_str(), &i);
    return i;
}


inline double GetDouble(const XMLElement* element, string name = "value")
{
    double d;
    element->QueryDoubleAttribute(name.c_str(), &d);
    return d;
}

inline string GetString(const XMLElement* element, string name)
{
    return element->Attribute(name.c_str());
}

void XMLParser::LoadParametersFromXML()
{
    XMLDocument doc;

    const string file = "C://Users//azer//workspace//Reza_Raytracer//xml_files//main.xml";
    cout << "Parsing " << file << '\n';
    XMLError eResult = doc.LoadFile(file.c_str());
    if (eResult != XML_SUCCESS)
    {
        cerr << "Cannot find " << file << '\n';
    }

    // ===== Root =====
    auto root = doc.FirstChild();

    // ===== Background gradient colors =====
    auto back_gradient_element = root->FirstChildElement("background_gradient");
    auto color1_element = back_gradient_element->FirstChildElement("color1");
    auto color2_element = back_gradient_element->FirstChildElement("color2");

    GlobalParameters::back_color1 = GetColor(color1_element);
    GlobalParameters::back_color2 = GetColor(color2_element);
    
    // ===== Camera =====
    auto camera_element = root->FirstChildElement("camera");
    if (camera_element == nullptr)
    {
        cerr << "Cannot find camera in the xml file\n";
    }
    auto lookfrom_element = camera_element->FirstChildElement("lookfrom");
    auto lookat_element   = camera_element->FirstChildElement("lookat");
    auto vup_element      = camera_element->FirstChildElement("vup");
    
    GlobalParameters::camera_lookfrom = GetVec3(lookfrom_element);
    GlobalParameters::camera_lookat   = GetVec3(lookat_element);
    GlobalParameters::camera_vup      = GetVec3(vup_element);
    
    // ===== Renderer =====
    auto renderer_element = root->FirstChildElement("renderer");
    if (renderer_element == nullptr)
    {
        cerr << "Cannot find renderer in the xml file\n";
    }

    auto image_width_element       = renderer_element->FirstChildElement("image_width");
    auto* samples_per_pixel_element = renderer_element->FirstChildElement("samples_per_pixel");
    auto max_depth_element         = renderer_element->FirstChildElement("max_depth");
    auto num_thread_element = renderer_element->FirstChildElement("num_thread");

    GlobalParameters::renderer_image_width       = GetInt(image_width_element);
    GlobalParameters::renderer_samples_per_pixel = GetInt(samples_per_pixel_element);
    GlobalParameters::renderer_max_depth         = GetInt(max_depth_element);

    GlobalParameters::num_thread = GetInt(num_thread_element);

    cout << "Done parsing\n\n";
}

void AddSphere(XMLElement* elem, 
    std::unordered_map<std::string, shared_ptr<Material>>& mat_map,
    std::vector<shared_ptr<Hittable>>& objects)
{
    string material_str = GetString(elem, "material_name");
    Point3 pos = GetVec3(elem->FirstChildElement("position"));
    double radius = stod(GetString(elem, "radius"));

    objects.push_back(make_shared<Sphere>(pos, radius, mat_map[material_str] ));
}

void AddTriangleMesh(XMLElement* elem, 
    std::unordered_map<std::string, shared_ptr<Material>>& mat_map,
    std::vector<shared_ptr<Hittable>>& objects)
{
    string material_str = GetString(elem, "material_name");

    std::vector<Vec3> vertices;                   // vertex list
    std::vector<Vec3> normals;                    // normal vector list
    std::vector<Vec2> uvs;                        // texture uvs
    std::vector<std::vector<int>> vertex_indices; // triangle faces
    std::vector<std::vector<int>> normal_indices; // normal vector indices for triangles
    std::vector<std::vector<int>> uv_indices;     // uv indices for triangles

    string filename = GetString(elem, "filename");
    Point3 pos = GetVec3(elem->FirstChildElement("position"));
    double scale = GetDouble(elem->FirstChildElement("scale"));

    OBJReader obj_reader;
    obj_reader.ReadOBJ(filename, 
                       vertices, 
                       normals, 
                       uvs,
                       vertex_indices, 
                       normal_indices,
                       uv_indices);

    for (int i = 0; i < vertex_indices.size(); i++)
    {
        int i1 = vertex_indices[i][0];
        int i2 = vertex_indices[i][1];
        int i3 = vertex_indices[i][2];

        Point3 p1 = vertices[i1] * scale + pos;
        Point3 p2 = vertices[i2] * scale + pos;
        Point3 p3 = vertices[i3] * scale + pos;

        if (normals.size() > 0)
        {
            i1 = normal_indices[i][0];
            i2 = normal_indices[i][1];
            i3 = normal_indices[i][2];

            Vec3 n1 = normals[i1];
            Vec3 n2 = normals[i2];
            Vec3 n3 = normals[i3];

            if (uvs.size() > 0)
            {
                // has vertices, normals, and uv coordinates

                i1 = uv_indices[i][0];
                i2 = uv_indices[i][1];
                i3 = uv_indices[i][2];

                Vec2 uv1 = uvs[i1];
                Vec2 uv2 = uvs[i2];
                Vec2 uv3 = uvs[i3];

                objects.push_back(make_shared<Triangle>(
                    p1,
                    p2,
                    p3,
                    n1,
                    n2,
                    n3,
                    uv1,
                    uv2,
                    uv3,
                    mat_map[material_str]));
            } // if (uvs.size() > 0)
            else
            {
                // has vertices and normals

                objects.push_back(make_shared<Triangle>(
                    p1,
                    p2,
                    p3,
                    n1,
                    n2,
                    n3,
                    mat_map[material_str]));
            }
        } // if (normals.size() > 0)
        else
        {
            // only has vertices

            objects.push_back(make_shared<Triangle>(
                p1,
                p2,
                p3,
                mat_map[material_str] ));
        } // else
    } // for (int i = 0; i < vertex_indices.size(); i++)
} // function ends here

void XMLParser::LoadObjects(std::unordered_map<std::string, shared_ptr<Texture>>& texture_map,
                            std::unordered_map<std::string, shared_ptr<Material>>& mat_map,
                            std::vector<shared_ptr<Hittable>>& objects)
{
    XMLDocument doc;
    const string file = "C://Users//azer//workspace//Reza_Raytracer//xml_files//main.xml";
    cout << "Parsing object on " << file << '\n';
    XMLError eResult = doc.LoadFile(file.c_str());
    if (eResult != XML_SUCCESS)
    {
        cerr << "Cannot find " << file << '\n';
    }

    // ===== Root =====
    auto root = doc.FirstChild();

    // ===== textures =====
    auto tex_parent_elem = root->FirstChildElement("textures");
    auto tex_elem = tex_parent_elem->FirstChildElement("texture");
    while (tex_elem != nullptr)
    {
        string name_str = GetString(tex_elem, "name");
        string type_str = GetString(tex_elem, "type");

        if (type_str == "checker")
        {
            auto color1_elem = tex_elem->FirstChildElement("color1");
            auto color2_elem = tex_elem->FirstChildElement("color2");
            auto frequency_elem = tex_elem->FirstChildElement("frequency");

            Color color1 = GetColor(color1_elem);
            Color color2 = GetColor(color2_elem);
            double frequency = GetDouble(frequency_elem);

            texture_map[name_str] = make_shared<CheckerTexture>(color1, color2, frequency);
        }

        tex_elem = tex_elem->NextSiblingElement();
    }

    // ===== materials =====
    auto mat_parent_elem = root->FirstChildElement("materials");
    auto mat_elem = mat_parent_elem->FirstChildElement("material");
    while (mat_elem != nullptr)
    {
        string name_str = GetString(mat_elem, "name");
        string type_str = GetString(mat_elem, "type");

        // create texture
        auto texture_ptr = shared_ptr<Texture>(nullptr);
        auto texture_elem = mat_elem->FirstChildElement("texture");
        if (texture_elem != nullptr)
        {
            // texture lookup
            string tex_str = GetString(texture_elem, "name");
            if (texture_map.find(tex_str) != texture_map.end())
            {
                texture_ptr = texture_map[tex_str];
            }
        }

        // if texture not found then create a solid color texture
        if (texture_ptr == nullptr)
        {
            auto color_elem = mat_elem->FirstChildElement("color");
            Color color = GetColor(color_elem);
            texture_ptr = make_shared<SolidColorTexture>(color);
        }

        if (type_str == "lambertian")
        {            
            mat_map[name_str] = make_shared<LambertianMaterial>(texture_ptr);
        }
        else if (type_str == "metal")
        {
            auto fuzzy_elem = mat_elem->FirstChildElement("fuzzy");
            double fuzzy = GetDouble(fuzzy_elem);

            mat_map[name_str] = make_shared<MetalMaterial>(texture_ptr, fuzzy);
        }

        mat_elem = mat_elem->NextSiblingElement();
    }
     
    // ===== Objects =====
    auto obj_parent_elem = root->FirstChildElement("objects");
    auto obj_elem = obj_parent_elem->FirstChildElement("object");
    while (obj_elem != nullptr)
    {
        string type_str =  GetString(obj_elem, "type");
        
        // TODO: create individual function for each object type
        if (type_str == "sphere")
        {
            AddSphere(obj_elem, mat_map, objects);
        }
        else if (type_str == "obj")
        {
            AddTriangleMesh(obj_elem, mat_map, objects);
        } 

        obj_elem = obj_elem->NextSiblingElement();
    }

    cout << "Done parsing objects\n\n";
}

