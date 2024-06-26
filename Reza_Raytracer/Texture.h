#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include "Vec3.h"
//#include <iostream> // debug purpose

class Texture
{
public:
	virtual Color Value(double u, double v, const Point3& p) const = 0;
};

class SolidColorTexture : public Texture
{
public:
	SolidColorTexture(Color c) : color_value(c)
	{
	}

	SolidColorTexture(double red, double green, double blue)
		: SolidColorTexture(Color(red, green, blue))
	{
	}

	Color Value(double u, double v, const Vec3& p) const override
	{
		return color_value;
	}

private:
	Color color_value;
};

// UV based checker texture on surface
class CheckerTexture : public Texture
{
public:
	CheckerTexture(shared_ptr<Texture> _even, shared_ptr<Texture> _odd, double _frequency)
		: even(_even),
		odd(_odd),
		frequency(_frequency)
	{
	}

	CheckerTexture(Color c1, Color c2, double _frequency)
		: even(make_shared<SolidColorTexture>(c1)),
		odd(make_shared<SolidColorTexture>(c2)),
		frequency(_frequency)
	{
	}

	Color Value(double u, double v, const Point3& p) const override
	{
		auto s = sin(frequency * u) * sin(frequency * v);

		if (s < 0.0)
		{
			return odd->Value(u, v, p);
		}
		else
		{
			return even->Value(u, v, p);
		}
	}

public:
	// Color 1
	shared_ptr<Texture> odd;

	// Color 2
	shared_ptr<Texture> even;

	// How many tiles you get
	double frequency;
};

// The original checker texture from Peter Shirley's Raytracing book.
// 3D volumetric checker pattern. 
class CheckerTexture2 : public Texture
{
public:
	CheckerTexture2(shared_ptr<Texture> _even, shared_ptr<Texture> _odd, double _frequency)
		: even(_even),
		odd(_odd),
		frequency(_frequency)
	{
	}

	CheckerTexture2(Color c1, Color c2, double _frequency)
		: even(make_shared<SolidColorTexture>(c1)),
		odd(make_shared<SolidColorTexture>(c2)),
		frequency(_frequency)
	{
	}

	Color Value(double u, double v, const Point3& p) const override
	{
		auto s = sin(frequency * p.x()) * sin(frequency * p.y()) * sin(frequency * p.z());

		if (s < 0.0)
		{
			return odd->Value(u, v, p);
		}
		else
		{
			return even->Value(u, v, p);
		}
	}

public:
	// Color 1
	shared_ptr<Texture> odd;

	// Color 2
	shared_ptr<Texture> even;

	// How many tiles you get
	double frequency;
};

#endif
