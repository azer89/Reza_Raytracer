

#include "Vec3.h"
#include "XMLParser.h"
#include "GlobalParameters.h"
#include "OBJReader.h"
#include "tinyxml2.h"


#include "Hittable.h"

#include "Material.h"

#include <iostream>

// C://Users//azer//workspace//Reza_Raytracer//scenes//main.xml
// tinyxml2.docsforge.com/master/examples/#read-attributes-and-text-information

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

inline int GetInt(const XMLElement* element)
{
    int i;

    element->QueryIntAttribute("value", &i);

    return i;
}


inline double GetDouble(const XMLElement* element)
{
    double d;

    element->QueryDoubleAttribute("value", &d);

    return d;
}

//#define TIXML_USE_STL

inline string GetString(const XMLElement* element, string name)
{
    return element->Attribute(name.c_str());
}

//XMLParser::XMLParser()
//{
//}

//XMLParser::~XMLParser()
//{
//}

void XMLParser::LoadParametersFromXML()
{
    XMLDocument doc;

    const string file = "C://Users//azer//workspace//Reza_Raytracer//scenes//main.xml";
    cout << "Parsing " << file << '\n';
    XMLError eResult = doc.LoadFile(file.c_str());
    if (eResult != XML_SUCCESS)
    {
        cerr << "Cannot find " << file << '\n';
    }

    // root
    XMLNode* root = doc.FirstChild();
    
    // camera
    XMLElement* camera_element = root->FirstChildElement("camera");
    if (camera_element == nullptr)
    {
        cerr << "Cannot find camera in the xml file\n";
    }
    XMLElement* lookfrom_element = camera_element->FirstChildElement("lookfrom");
    XMLElement* lookat_element   = camera_element->FirstChildElement("lookat");
    XMLElement* vup_element      = camera_element->FirstChildElement("vup");
    
    GlobalParameters::camera_lookfrom = GetVec3(lookfrom_element);
    GlobalParameters::camera_lookat   = GetVec3(lookat_element);
    GlobalParameters::camera_vup      = GetVec3(vup_element);
    
    // renderer
    XMLElement* renderer_element = root->FirstChildElement("renderer");
    if (renderer_element == nullptr)
    {
        cerr << "Cannot find renderer in the xml file\n";
    }
    XMLElement* image_width_element       = renderer_element->FirstChildElement("image_width");
    XMLElement* samples_per_pixel_element = renderer_element->FirstChildElement("samples_per_pixel");
    XMLElement* max_depth_element         = renderer_element->FirstChildElement("max_depth");


    GlobalParameters::renderer_image_width       = GetInt(image_width_element);
    GlobalParameters::renderer_samples_per_pixel = GetInt(samples_per_pixel_element);
    GlobalParameters::renderer_max_depth         = GetInt(max_depth_element);

    cout << "Done parsing\n\n";
}

void XMLParser::LoadMaterials(std::unordered_map<std::string, shared_ptr<Material>>& mat_map)
{
    XMLDocument doc;

    const string file = "C://Users//azer//workspace//Reza_Raytracer//scenes//main.xml";
    cout << "Parsing materials on " << file << '\n';
    XMLError eResult = doc.LoadFile(file.c_str());
    if (eResult != XML_SUCCESS)
    {
        cerr << "Cannot find " << file << '\n';
    }

    // root
    XMLNode* root = doc.FirstChild();
    XMLElement* mat_root = root->FirstChildElement("materials");
    XMLElement* mat_elem = mat_root->FirstChildElement("material");
    while (mat_elem != nullptr)
    {
        string name_str = GetString(mat_elem, "name");
        string type_str = GetString(mat_elem, "type");
        XMLElement* color_elem = mat_elem->FirstChildElement("color");
        Color mat_color = GetColor(color_elem);

        if (type_str == "lambertian")
        {
            mat_map[name_str] = make_shared<Lambertian>(mat_color);
        }
        else if (type_str == "metal")
        {
            mat_map[name_str] = make_shared<Metal>(mat_color);
        }

        mat_elem = mat_elem->NextSiblingElement();
    }

    cout << "Done parsing materials\n\n";
}
//
void XMLParser::LoadObjects(std::vector<shared_ptr<Hittable>>& objects)
{
//    XMLDocument doc;
//
//    const string file = "C://Users//azer//workspace//Reza_Raytracer//scenes//main.xml";
//    cout << "Parsing materials on " << file << '\n';
//    XMLError eResult = doc.LoadFile(file.c_str());
//    if (eResult != XML_SUCCESS)
//    {
//        cerr << "Cannot find " << file << '\n';
//    }
//
//    // root
//    XMLNode* root = doc.FirstChild();
//
//    cout << "Done parsing materials\n\n";
}

