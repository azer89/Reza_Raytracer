#include "Camera.h"
#include "GlobalParameters.h"

Camera::Camera()
{
    lookfrom = GlobalParameters::camera_lookfrom;
    lookat   = GlobalParameters::camera_lookat;
    vup      = GlobalParameters::camera_vup;

    // TODO: to XML
    vfov = GlobalParameters::camera_vfov;
    aspect_ratio = GlobalParameters::camera_aspect_ratio;

    auto theta = UsefulFunct::DegreesToRadians(vfov);

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
    auto u = UnitVector(Cross(vup, w));     // x
    auto v = Cross(w, u);                   // y

    origin = lookfrom;
    horizontal = viewport_width * u;
    vertical = viewport_height * v;
    lower_left_corner = origin - horizontal / 2 - vertical / 2 - w;
}

Ray3 Camera::GetRay(double s, double t) const
{
	return Ray3(origin, 
				lower_left_corner + (s * horizontal) + (t * vertical) - origin );
}