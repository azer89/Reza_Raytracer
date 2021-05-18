

#include "Vec3.h"
#include "XMLParameters.h"
#include "tinyxml2.h"

#include <iostream>

// C://Users//azer//workspace//Reza_Raytracer//scenes//main.xml
// tinyxml2.docsforge.com/master/examples/#read-attributes-and-text-information

using namespace tinyxml2;
using namespace std;

inline Vec3 GetVec3(XMLElement& element)
{
    double x;
    double y;
    double z;

    element.QueryDoubleAttribute("x", &x);
    element.QueryDoubleAttribute("y", &y);
    element.QueryDoubleAttribute("z", &z);

    return Vec3(x, y, z);
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

    XMLNode* root = doc.FirstChild();
    XMLElement* camera_element = root->FirstChildElement("camera");
    if (camera_element == nullptr)
    {
        cerr << "Cannot find came in the xml file\n";
    }
    /*
    Point3 camera_lookfrom;
	Point3 camera_lookat;
	Vec3   camera_vup;
    */
    XMLElement* lookfrom_element = camera_element->FirstChildElement("lookfrom");
    XMLElement* lookat_element = camera_element->FirstChildElement("lookat");
    XMLElement* vup_element = camera_element->FirstChildElement("vup");
    

    
    //if (pRoot == nullptr) throw XML_ERROR_FILE_READ_ERROR;
}