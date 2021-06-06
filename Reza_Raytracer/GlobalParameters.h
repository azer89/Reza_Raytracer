#ifndef __GLOBAL_PARAMETERS_H__
#define __GLOBAL_PARAMETERS_H__

#include "Vec3.h"

struct GlobalParameters
{
public:
	// Camera
	static Point3 camera_lookfrom;
	static Point3 camera_lookat;
	static Vec3   camera_vup;

	// Cackground gradient colors
	static Color back_color1;
	static Color back_color2;

	// Renderer
	static int renderer_image_width;
	static int renderer_samples_per_pixel;
	static int renderer_max_depth;

	// Multithreading
	static int num_thread;
};


#endif
