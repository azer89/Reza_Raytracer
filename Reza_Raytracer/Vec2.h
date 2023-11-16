#ifndef __VEC_2_H__
#define __VEC_2_H__

#include <cmath>
#include <ostream>

class Vec2
{
public:
	double e[2];

public:
	Vec2() : e{ 0,0 }
	{
	}

	Vec2(double e0, double e1) : e{ e0, e1 }
	{
	}

	double x() const { return e[0]; }
	double y() const { return e[1]; }

	Vec2 operator-() const
	{
		return Vec2(-e[0], -e[1]);
	}

	double operator[](int i) const
	{
		return e[i];
	}

	double& operator[](int i)
	{
		return e[i];
	}

	Vec2& operator+=(const Vec2& v)
	{
		e[0] += v.e[0];
		e[1] += v.e[1];
		return *this;
	}

	Vec2& operator*=(const double t)
	{
		e[0] *= t;
		e[1] *= t;
		return *this;
	}

	Vec2& operator/=(const double t)
	{
		return *this *= 1 / t;
	}

	double Length() const
	{
		return sqrt(LengthSquared());
	}

	double LengthSquared() const
	{
		return e[0] * e[0] + e[1] * e[1];
	}
};

// Type aliases
using Point2 = Vec2;   // 2D point

/*
	Operator overloading
*/

inline std::ostream& operator<<(std::ostream& out, const Vec2& v)
{
	return out << v.e[0] << ' ' << v.e[1];
}

inline Vec2 operator+(const Vec2& u, const Vec2& v)
{
	return Vec2(u.e[0] + v.e[0], u.e[1] + v.e[1]);
}

inline Vec2 operator-(const Vec2& u, const Vec2& v)
{
	return Vec2(u.e[0] - v.e[0], u.e[1] - v.e[1]);
}

inline Vec2 operator*(const Vec2& u, const Vec2& v)
{
	return Vec2(u.e[0] * v.e[0], u.e[1] * v.e[1]);
}

inline Vec2 operator*(double t, const Vec2& v)
{
	return Vec2(t * v.e[0], t * v.e[1]);
}

inline Vec2 operator*(const Vec2& v, double t)
{
	return t * v;
}

inline Vec2 operator/(Vec2 v, double t)
{
	return (1 / t) * v;
}

/*
	Utility functions
*/

inline double Dot(const Vec2& u, const Vec2& v)
{
	return u.e[0] * v.e[0] + u.e[1] * v.e[1];
}

inline Vec2 UnitVector(Vec2 v)
{
	return v / v.Length();
}

inline Vec2 Reflect(const Vec2& v, const Vec2& n)
{
	return v - 2 * Dot(v, n) * n;
}

#endif