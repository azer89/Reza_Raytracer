#include "Vec3.h"
#include "XMLParser.h"
#include "GlobalParameters.h"
#include "OBJReader.h"
#include "Hittable.h"
#include "Sphere.h"
#include "Triangle.h"
#include "AARect.h"
#include "Texture.h"
#include "Material.h"

#include "tinyxml2.h"

#include <iostream>

// C://Users//azer//workspace//Reza_Raytracer//scenes//main.xml

using namespace tinyxml2;
using namespace std;

inline Vec3 GetVec3(const XMLElement* elem)
{
    double x;
    double y;
    double z;

    elem->QueryDoubleAttribute("x", &x);
    elem->QueryDoubleAttribute("y", &y);
    elem->QueryDoubleAttribute("z", &z);

    return Vec3(x, y, z);
}

inline Color GetColor(const XMLElement* elem)
{
    double r;
    double g;
    double b;

    elem->QueryDoubleAttribute("r", &r);
    elem->QueryDoubleAttribute("g", &g);
    elem->QueryDoubleAttribute("b", &b);

    return Color(r, g, b);
}

inline int GetInt(const XMLElement* elem, string name = "value")
{
    int i;
    elem->QueryIntAttribute(name.c_str(), &i);
    return i;
}

inline double GetDouble(const XMLElement* elem, string name = "value")
{
    double d;
    elem->QueryDoubleAttribute(name.c_str(), &d);
    return d;
}

inline string GetString(const XMLElement* elem, string name)
{
    return elem->Attribute(name.c_str());
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
    auto back_gradient_elem = root->FirstChildElement("background_gradient");
    auto color1_elem = back_gradient_elem->FirstChildElement("color1");
    auto color2_elem = back_gradient_elem->FirstChildElement("color2");

    GlobalParameters::back_color1 = GetColor(color1_elem);
    GlobalParameters::back_color2 = GetColor(color2_elem);
    
    // ===== Camera =====
    auto camera_elem = root->FirstChildElement("camera");
    if (camera_elem == nullptr)
    {
        cerr << "Cannot find camera in the xml file\n";
    }
    auto lookfrom_elem = camera_elem->FirstChildElement("lookfrom");
    auto lookat_elem   = camera_elem->FirstChildElement("lookat");
    auto vup_elem      = camera_elem->FirstChildElement("vup");
    
    GlobalParameters::camera_lookfrom = GetVec3(lookfrom_elem);
    GlobalParameters::camera_lookat   = GetVec3(lookat_elem);
    GlobalParameters::camera_vup      = GetVec3(vup_elem);
    
    // ===== Renderer =====
    auto renderer_elem = root->FirstChildElement("renderer");
    if (renderer_elem == nullptr)
    {
        cerr << "Cannot find renderer in the xml file\n";
    }

    auto image_width_elem       = renderer_elem->FirstChildElement("image_width");
    auto samples_per_pixel_elem = renderer_elem->FirstChildElement("samples_per_pixel");
    auto max_depth_elem         = renderer_elem->FirstChildElement("max_depth");
    auto thin_padding_elem      = renderer_elem->FirstChildElement("thin_padding");
    auto min_t_elem             = renderer_elem->FirstChildElement("min_t");
    auto num_thread_elem        = renderer_elem->FirstChildElement("num_thread");

    GlobalParameters::renderer_image_width       = GetInt(image_width_elem);
    GlobalParameters::renderer_samples_per_pixel = GetInt(samples_per_pixel_elem);
    GlobalParameters::renderer_max_depth         = GetInt(max_depth_elem);
    GlobalParameters::thin_padding               = GetDouble(thin_padding_elem);
    GlobalParameters::min_t                      = GetDouble(min_t_elem);
    GlobalParameters::num_thread                 = GetInt(num_thread_elem);

    cout << "Done parsing\n\n";
}

// XZ
void AddXZRect(XMLElement* elem,
    std::unordered_map<std::string, shared_ptr<Material>>& mat_map,
    std::vector<shared_ptr<Hittable>>& objects)
{
    string material_str = GetString(elem, "material_name");
    auto boundary_elem = elem->FirstChildElement("boundary");
    double x0 = GetDouble(boundary_elem, "x0");
    double x1 = GetDouble(boundary_elem, "x1");
    double z0 = GetDouble(boundary_elem, "z0");
    double z1 = GetDouble(boundary_elem, "z1");
    double y  = GetDouble(boundary_elem, "y");

    objects.emplace_back(make_shared<XZRect>(x0, x1, z0, z1, y, mat_map[material_str]));
}

// XY
void AddXYRect(XMLElement* elem,
    std::unordered_map<std::string, shared_ptr<Material>>& mat_map,
    std::vector<shared_ptr<Hittable>>& objects)
{
    string material_str = GetString(elem, "material_name");
    auto boundary_elem = elem->FirstChildElement("boundary");
    double x0 = GetDouble(boundary_elem, "x0");
    double x1 = GetDouble(boundary_elem, "x1");
    double y0 = GetDouble(boundary_elem, "y0");
    double y1 = GetDouble(boundary_elem, "y1");
    double z  = GetDouble(boundary_elem, "z");

    objects.emplace_back(make_shared<XZRect>(x0, x1, y0, y1, z, mat_map[material_str]));
}

// YZ
void AddYZRect(XMLElement* elem,
    std::unordered_map<std::string, shared_ptr<Material>>& mat_map,
    std::vector<shared_ptr<Hittable>>& objects)
{
    string material_str = GetString(elem, "material_name");
    auto boundary_elem = elem->FirstChildElement("boundary");
    double y0 = GetDouble(boundary_elem, "y0");
    double y1 = GetDouble(boundary_elem, "y1");
    double z0 = GetDouble(boundary_elem, "z0");
    double z1 = GetDouble(boundary_elem, "z1");
    double x  = GetDouble(boundary_elem, "y");

    objects.emplace_back(make_shared<XZRect>(y0, y1, z0, z1, x, mat_map[material_str]));
}

void AddSphere(XMLElement* elem,
    std::unordered_map<std::string, shared_ptr<Material>>& mat_map,
    std::vector<shared_ptr<Hittable>>& objects)
{
    string material_str = GetString(elem, "material_name");
    Point3 pos = GetVec3(elem->FirstChildElement("position"));
    double radius = stod(GetString(elem, "radius"));

    objects.emplace_back(make_shared<Sphere>(pos, radius, mat_map[material_str]));
}

void AddCornellBox(std::unordered_map<std::string, shared_ptr<Texture>>& texture_map,
    std::unordered_map<std::string, shared_ptr<Material>>& mat_map,
    std::vector<shared_ptr<Hittable>>& objects)
{
    // TODO: Tidying

    texture_map["cornell_red_tex"] = make_shared<SolidColorTexture>(Color(0.65, 0.05, 0.05)); // red
    texture_map["cornell_white_tex"] = make_shared<SolidColorTexture>(Color(0.73, 0.73, 0.73)); // white
    texture_map["cornell_green_tex"] = make_shared<SolidColorTexture>(Color(0.12, 0.45, 0.15)); // green
    texture_map["cornell_light_tex"] = make_shared<SolidColorTexture>(Color(15, 15, 15)); // light

    mat_map["cornell_red_mat"] = make_shared<LambertianMaterial>(texture_map["cornell_red_tex"]); // red
    mat_map["cornell_white_mat"] = make_shared<LambertianMaterial>(texture_map["cornell_white_tex"]); // white
    mat_map["cornell_green_mat"] = make_shared<LambertianMaterial>(texture_map["cornell_green_tex"]); // green
    mat_map["cornell_light_mat"] = make_shared<DiffuseLightMaterial>(texture_map["cornell_light_tex"]); // light

    objects.emplace_back(make_shared<YZRect>(0, 555, 0, 555, 555, mat_map["cornell_green_mat"]));
    objects.emplace_back(make_shared<YZRect>(0, 555, 0, 555, 0, mat_map["cornell_red_mat"]));
    objects.emplace_back(make_shared<XZRect>(213, 343, 227, 332, 554, mat_map["cornell_light_mat"]));
    //objects.emplace_back(make_shared<XZRect>(0, 555, 0, 555, 0, mat_map["cornell_white_mat"]));
    //objects.emplace_back(make_shared<XZRect>(0, 555, 0, 555, 555, mat_map["cornell_white_mat"]));
    //objects.emplace_back(make_shared<XYRect>(0, 555, 0, 555, 555, mat_map["cornell_white_mat"]));
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

    for (size_t i = 0; i < vertex_indices.size(); i++)
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

                objects.emplace_back(make_shared<Triangle>(
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

                objects.emplace_back(make_shared<Triangle>(
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

            objects.emplace_back(make_shared<Triangle>(
                p1,
                p2,
                p3,
                mat_map[material_str]));
        } // else
    } // for (size_t i = 0; i < vertex_indices.size(); i++)
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

        //if (type_str == "checker" || type_str == "checker2")
        if(type_str.rfind("checker") == 0)
        {
            auto color1_elem = tex_elem->FirstChildElement("color1");
            auto color2_elem = tex_elem->FirstChildElement("color2");
            auto frequency_elem = tex_elem->FirstChildElement("frequency");

            Color color1 = GetColor(color1_elem);
            Color color2 = GetColor(color2_elem);
            double frequency = GetDouble(frequency_elem);

            if (type_str == "checker")
            {
                texture_map[name_str] = make_shared<CheckerTexture>(color1, color2, frequency);
            }
            else
            {
                texture_map[name_str] = make_shared<CheckerTexture2>(color1, color2, frequency);
            }
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
        else if (type_str == "diffuselight")
        {
            mat_map[name_str] = make_shared<DiffuseLightMaterial>(texture_ptr);
        }
        else if (type_str == "dielectric")
        {
            auto ridx_elem = mat_elem->FirstChildElement("refraction_index");
            double refraction_index = GetDouble(ridx_elem);

            mat_map[name_str] = make_shared<DielectricMaterial>(texture_ptr, refraction_index);
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
        else if (type_str == "xzrect")
        {
            AddXZRect(obj_elem, mat_map, objects);
        }
        else if (type_str == "xyrect")
        {
            AddXYRect(obj_elem, mat_map, objects);
        }
        else if (type_str == "yzrect")
        {
            AddYZRect(obj_elem, mat_map, objects);
        }
        else if (type_str == "cornell_box")
        {
            AddCornellBox(texture_map, mat_map, objects);
        }

        obj_elem = obj_elem->NextSiblingElement();
    }

    cout << "Done parsing objects\n\n";
}


