#ifndef __AABB__
#define __AABB__

#include "Vec3.h"
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

	// cannot put this function definition in a cpp file, I'm so confused
	bool Hit(const Ray3& r, double t_min, double t_max) const
	{
		// readable version
		/*for (int a = 0; a < 3; a++)
		{
			auto t0 = fmin((minimum[a] - r.Origin()[a]) / r.Direction()[a], (maximum[a] - r.Origin()[a]) / r.Direction()[a]);
			auto t1 = fmax((minimum[a] - r.Origin()[a]) / r.Direction()[a], (maximum[a] - r.Origin()[a]) / r.Direction()[a]);

			t_min = fmax(t0, t_min);
			t_max = fmin(t1, t_max);

			if (t_max <= t_min)
			{
				return false;
			}
		}
		return true;*/

		// optimized version
		for (int a = 0; a < 3; a++)
		{
			auto invDir = 1.0f / r.Direction()[a];
			auto t0 = (Min()[a] - r.Origin()[a]) * invDir;
			auto t1 = (Max()[a] - r.Origin()[a]) * invDir;

			// if direction is reversed
			if (invDir < 0.0)
			{
				std::swap(t0, t1);
			}

			// if AABB intersects [t_min, t_max]
			t_min = t0 > t_min ? t0 : t_min;
			t_max = t1 < t_max ? t1 : t_max;
			if (t_max <= t_min)
			{
				return false;
			}
		}
		return true;
	}
	

private:
	Point3 maximum;
	Point3 minimum;
};

#endif