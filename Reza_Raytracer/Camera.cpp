
#include "Camera.h"


/*
double aspect_ratio;
double viewport_height;
double viewport_width;
double focal_length;

Point3 origin;
Vec3 horizontal;
Vec3 vertical;
Point3 lower_left_corner;
 */
Camera::Camera()
{
    /*
    (-2,2,1)
    (0,0,-1)
    (0,1,0)
     */
    lookfrom = Point3(2, 3, 2);
    lookat = Point3(0, 0, -1);
    vup = Vec3(0, 1, 0);
	
    this->vfov = 30; // in degree
    this->aspect_ratio = 16.0 / 9.0;
	
    auto theta = DegreesToRadians(vfov);

	/*
	tan theta = h / z
	where
		z is vector pointing to scene
		h is the width or height
	assume z = 1
	then
		h = tan theta * z
		h = tan theta * 1
	 */
    auto h = tan(theta / 2);
    viewport_height = 2.0 * h;
    viewport_width = aspect_ratio * viewport_height;

    auto w = UnitVector(lookfrom - lookat);
    auto u = UnitVector(Cross(vup, w));
    auto v = Cross(w, u);

    origin = lookfrom;
    horizontal = viewport_width * u;
    vertical = viewport_height * v;
    lower_left_corner = origin - horizontal / 2 - vertical / 2 - w;
}

/*
Camera::Camera()
{
    aspect_ratio = 16.0 / 9.0;
    auto viewport_height = 2.0;
    auto viewport_width = aspect_ratio * viewport_height;
    auto focal_length = 1.0;

    origin = Point3(0, 0, 0);
    horizontal = Vec3(viewport_width, 0.0, 0.0);
    vertical = Vec3(0.0, viewport_height, 0.0);
    lower_left_corner = origin - horizontal / 2 - vertical / 2 - Vec3(0, 0, focal_length);
}*/

Ray3 Camera::GetRay(double s, double t) const
{
    //return Ray3(origin, lower_left_corner + u * horizontal + v * vertical - origin);
     return  Ray3(origin, lower_left_corner + s * horizontal + t * vertical - origin);
}