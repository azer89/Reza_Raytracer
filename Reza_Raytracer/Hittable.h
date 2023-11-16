#ifndef __HITTABLE_H__
#define __HITTABLE_H__

#include "HitRecord.h"
#include "Ray3.h"
#include "AABB.h"

class Material;

class Hittable
{
public:
	// More about ray interections:
	// www.iquilezles.org/www/articles/intersectors/intersectors.htm
	virtual bool Hit(const Ray3& r, double t_min, double t_max, HitRecord& rec) const = 0;

	virtual bool BoundingBox(AABB& output_box) const = 0;
};

#endif
