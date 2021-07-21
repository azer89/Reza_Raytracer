#ifndef __AA_RECT__
#define __AA_RECT__

#include "Hittable.h"

// github.com/RayTracing/raytracing.github.io/blob/master/src/TheNextWeek/aarect.h

class XZRect : public Hittable
{
public:
	// Constructor
	XZRect(double _x0, 
		   double _x1, 
		   double _z0, 
		   double _z1, 
		   double _y, 
		   shared_ptr<Material>& mat) :
		x0(_x0),
		x1(_x1),
		z0(_z0),
		z1(_z1),
		y(_y),
		material_ptr(mat)
	{
	}

	bool Hit(const Ray3& r,
			 double t_min,
			 double t_max,
			 HitRecord& rec) const override;

	bool BoundingBox(AABB& output_box) const override;

public:
	shared_ptr<Material> material_ptr;

	double x0;
	double x1;
	double z0;
	double z1;

	double y;
};

#endif
