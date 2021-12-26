#ifndef __AA_RECT__
#define __AA_RECT__

/*Axis Aligned Rectangles*/

#include "Hittable.h"

// XZ
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

// XY
class XYRect : public Hittable
{
public:
	// Constructor
	XYRect(double _x0,
		double _x1,
		double _y0,
		double _y1,
		double _z,
		shared_ptr<Material>& mat) :
		x0(_x0),
		x1(_x1),
		y0(_y0),
		y1(_y1),
		z(_z),
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
	double y0;
	double y1;

	double z;
};

// YZ
class YZRect : public Hittable
{
public:
	// Constructor
	YZRect(double _y0,
		double _y1,
		double _z0,
		double _z1,
		double _x,
		shared_ptr<Material>& mat) :
		y0(_y0),
		y1(_y1),
		z0(_z0),
		z1(_z1),
		x(_x),
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

	double y0;
	double y1;
	double z0;
	double z1;

	double x;
};

#endif
