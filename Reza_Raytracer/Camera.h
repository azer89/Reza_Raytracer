#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "Ray3.h"
#include "Vec3.h"

class Camera
{
public:
	Camera();

	Ray3 GetRay(double s, double t) const;

	double GetAspectRatio() const
	{
		return aspect_ratio;
	}

private:
	double vfov; // Vertical field-of-view in degrees
	double aspect_ratio;

	double viewport_height;
	double viewport_width;
	//double focal_length;

	Point3 origin;
	Point3 lower_left_corner;
	Vec3 horizontal;
	Vec3 vertical;

	Point3 lookfrom;
	Point3 lookat;
	Vec3   vup; // Vector up
};

#endif

