#ifndef __AABB__
#define __AABB__

#include "Ray3.h"

class AABB
{
	AABB()
	{
	}

	// Constructor
	AABB(const Point3& a, const Point3& b)
	{
		minimum = a;
		maximum = b;
	}

	Point3 Min() const
	{
		return minimum;
	}

	Point3 Max() const
	{
		return maximum;
	}
	
	bool Hit(const Ray3& r, double t_min, double t_max) const;

private:
	Point3 maximum;
	Point3 minimum;
};

#endif