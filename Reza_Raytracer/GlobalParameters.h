#ifndef __GLOBAL_PARAMETERS_H__
#define __GLOBAL_PARAMETERS_H__

#include "Vec3.h"

namespace GlobalParameters
{
	// Camera
	extern Point3 camera_lookfrom;
	extern Point3 camera_lookat;
	extern Vec3   camera_vup;

	// Background gradient colors
	extern Color back_color1;
	extern Color back_color2;

	// Renderer
	extern int renderer_image_width;
	extern int renderer_samples_per_pixel;
	extern int renderer_max_depth;

	// Multithreading
	extern int num_thread;

	// Thin object padding (planes or triangles)
	extern double thin_padding;

	// Minimum distance for ray intersections
	extern double min_t;
}

#endif
