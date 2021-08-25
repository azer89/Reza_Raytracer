#include "GlobalParameters.h"

Point3 GlobalParameters::camera_lookfrom = Point3();
Point3 GlobalParameters::camera_lookat = Point3();
Vec3 GlobalParameters::camera_vup = Vec3();
double GlobalParameters::camera_vfov = 0;
double GlobalParameters::camera_aspect_ratio = 0;

Color GlobalParameters::back_color1 = Color(1.0, 1.0, 1.0);
Color GlobalParameters::back_color2 = Color(1.0, 1.0, 1.0);

int GlobalParameters::renderer_image_width = 0;
int GlobalParameters::renderer_samples_per_pixel = 0;
int GlobalParameters::renderer_max_depth = 0;

int GlobalParameters::num_thread = 1;

double GlobalParameters::thin_padding = 1e-5;

double GlobalParameters::min_t = 0.001;
