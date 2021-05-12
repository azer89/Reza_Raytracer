#ifndef __AABB__
#define __AABB__

#include "Ray3.h"

class AABB
{
public:
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


inline AABB SurroundingBox(AABB box0, AABB box1)
{
	Point3 small(fmin(box0.Min().x(), box1.Min().x()),
				 fmin(box0.Min().y(), box1.Min().y()),
				 fmin(box0.Min().z(), box1.Min().z()));

	Point3 big(fmax(box0.Max().x(), box1.Max().x()),
			   fmax(box0.Max().y(), box1.Max().y()),
			   fmax(box0.Max().z(), box1.Max().z()));

	return AABB(small, big);
}

#endif