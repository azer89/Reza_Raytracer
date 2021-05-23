
#include "Camera.h"

#include "XMLParameters.h"

Camera::Camera()
{
    /*
    (-2,2,1)
    (0,0,-1)
    (0,1,0)
     */
    /*lookfrom = Point3(2, 1.5, 2);
    lookat = Point3(0, 0, -1);
    vup = Vec3(0, 1, 0);
	*/

    //lookfrom = Point3(0, 0, 2.3);
    //lookat = Point3(0, 0, -1);
    //vup = Vec3(0, 1, 0);
    lookfrom = XMLParameters::camera_lookfrom;
    lookat = XMLParameters::camera_lookat;
    vup = XMLParameters::camera_vup;

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

	// u, v, w are the orthonormal basis
	// note that vup,v, w lie on the same plane
    auto w = UnitVector(lookfrom - lookat); // z
    auto u = UnitVector(Cross(vup, w)); // x
    auto v = Cross(w, u);                 // y

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
    /*
    Point3 origin;
    Point3 lower_left_corner;
    Vec3 horizontal;
    Vec3 vertical;
     */
	
    //return Ray3(origin, lower_left_corner + u * horizontal + v * vertical - origin);
	return Ray3(origin, 
				lower_left_corner + (s * horizontal) + (t * vertical) - origin );
}