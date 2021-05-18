#ifndef __XMLPARAMETERS_H__
#define __XMLPARAMETERS_H__

#include "Vec3.h"

// A class that contains parameters taken from main.xml
// Also a wrapper to tinyxml2
class XMLParameters
{
public:
	XMLParameters();
	~XMLParameters();

	static void LoadParametersFromXML();

public:
	Point3 camera_lookfrom;
	Point3 camera_lookat;
	Vec3   camera_vup;
};

#endif
