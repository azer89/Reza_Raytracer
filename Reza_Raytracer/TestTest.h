#ifndef __Test_Test__
#define __Test_Test__

#include "Ray3.h"

class TestTest
{
	TestTest()
	{
	}

	// Constructor
	TestTest(const Point3& a, const Point3& b)
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
	
	bool Hit_AABB(const Ray3& r, double t_min, double t_max);

	private:
		Point3 maximum;
		Point3 minimum;
};

#endif