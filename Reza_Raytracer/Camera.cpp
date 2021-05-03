
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
Camera::Camera(double vfov, // vertical field-of-view in degrees
			double aspect_ratio)
{
    this->aspect_ratio = aspect_ratio;
	
    auto theta = DegreesToRadians(vfov);
    auto h = tan(theta / 2);
    viewport_height = 2.0 * h;
    viewport_width = aspect_ratio * viewport_height;

    focal_length = 1.0;

    origin = Point3(0, 0, 0);
    horizontal = Vec3(viewport_width, 0.0, 0.0);
    vertical = Vec3(0.0, viewport_height, 0.0);
    lower_left_corner = origin - horizontal / 2 - vertical / 2 - Vec3(0, 0, focal_length);
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

Ray3 Camera::GetRay(double u, double v) const
{
    return Ray3(origin, lower_left_corner + u * horizontal + v * vertical - origin);
}