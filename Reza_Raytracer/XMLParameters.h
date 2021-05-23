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
	// camera
	static Point3 camera_lookfrom;
	static Point3 camera_lookat;
	static Vec3   camera_vup;

	// renderer
	static int renderer_image_width;
	static int renderer_samples_per_pixel;
	static int renderer_max_depth;
};

#endif
