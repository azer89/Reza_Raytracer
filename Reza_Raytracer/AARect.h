#ifndef __AA_RECT__
#define __AA_RECT__

#include "Hittable.h"

// github.com/RayTracing/raytracing.github.io/blob/master/src/TheNextWeek/aarect.h
class XZRect : public Hittable
{
public:


public:
	shared_ptr<Material> material_ptr;

	double x0;
	double x1;
	double z0;
	double z1;

	double y;
};

#endif
