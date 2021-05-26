#ifndef __GLOBAL_PARAMETERS_H__
#define __GLOBAL_PARAMETERS_H__

#include "Vec3.h"

struct GlobalParameters
{
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
