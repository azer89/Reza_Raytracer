#ifndef __AABB__
#define __AABB__

#include "Vec3.h"

class AABB
{
private:
	Point3 maximum;
	Point3 minimum;
	
public:
	// Constructor
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

	bool Hit(const Ray3& r, double t_min, double t_max) const
	{
		for (int a = 0; a < 3; a++) 
		{
			auto t0 = fmin((minimum[a] - r.origin()[a]) / r.direction()[a], (maximum[a] - r.origin()[a]) / r.direction()[a]);
			auto t1 = fmax((minimum[a] - r.origin()[a]) / r.direction()[a], (maximum[a] - r.origin()[a]) / r.direction()[a]);

			t_min = fmax(t0, t_min);
			t_max = fmin(t1, t_max);

			if (t_max <= t_min)
			{
				return false;
			}
		}
		return true;
	}

	
};

#endif