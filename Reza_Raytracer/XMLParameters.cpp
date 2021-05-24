

#include "Vec3.h"
#include "XMLParameters.h"
#include "tinyxml2.h"

#include <iostream>

// C://Users//azer//workspace//Reza_Raytracer//scenes//main.xml
// tinyxml2.docsforge.com/master/examples/#read-attributes-and-text-information

using namespace tinyxml2;
using namespace std;

inline Vec3 GetVec3(XMLElement* element)
{
    double x;
    double y;
    double z;

    element->QueryDoubleAttribute("x", &x);
    element->QueryDoubleAttribute("y", &y);
    element->QueryDoubleAttribute("z", &z);

    return Vec3(x, y, z);
}

inline int GetInt(XMLElement* element)
{
    int i;

    element->QueryIntAttribute("value", &i);

    return i;
}


inline double GetDouble(XMLElement* element)
{
    double d;

    element->QueryDoubleAttribute("value", &d);

    return d;
}

XMLParameters::XMLParameters()
{
}

XMLParameters::~XMLParameters()
{
}

void XMLParameters::LoadParametersFromXML()
{
    XMLDocument doc;

    string file = "C://Users//azer//workspace//Reza_Raytracer//scenes//main.xml";
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
    
    XMLParameters::camera_lookfrom = GetVec3(lookfrom_element);
    XMLParameters::camera_lookat   = GetVec3(lookat_element);
    XMLParameters::camera_vup      = GetVec3(vup_element);
    
    // renderer
    XMLElement* renderer_element = root->FirstChildElement("renderer");
    if (renderer_element == nullptr)
    {
        cerr << "Cannot find renderer in the xml file\n";
    }
    XMLElement* image_width_element       = renderer_element->FirstChildElement("image_width");
    XMLElement* samples_per_pixel_element = renderer_element->FirstChildElement("samples_per_pixel");
    XMLElement* max_depth_element         = renderer_element->FirstChildElement("max_depth");

    XMLParameters::renderer_image_width       = GetInt(image_width_element);
    XMLParameters::renderer_samples_per_pixel = GetInt(samples_per_pixel_element);
    XMLParameters::renderer_max_depth         = GetInt(max_depth_element);

    cout << "Done parsing\n\n";
}

Point3 XMLParameters::camera_lookfrom = Point3();
Point3 XMLParameters::camera_lookat   = Point3();
Vec3 XMLParameters::camera_vup        = Vec3();

int XMLParameters::renderer_image_width       = 0;
int XMLParameters::renderer_samples_per_pixel = 0;
int XMLParameters::renderer_max_depth         = 0;