
#include "GlobalParameters.h"

Point3 GlobalParameters::camera_lookfrom = Point3();
Point3 GlobalParameters::camera_lookat = Point3();
Vec3 GlobalParameters::camera_vup = Vec3();

int GlobalParameters::renderer_image_width = 0;
int GlobalParameters::renderer_samples_per_pixel = 0;
int GlobalParameters::renderer_max_depth = 0;

// if it's more than one then 
int GlobalParameters::num_thread = 1;
