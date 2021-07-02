#ifndef __VEC_3_H__
#define __VEC_3_H__

#include <cmath>
#include <ostream>

using std::sqrt;

#include "UsefulThings.h"

class Vec3
{
public:
	double e[3];

public:
    Vec3() : e{ 0,0,0 }
    {	    
    }
	
    Vec3(double e0, double e1, double e2) : e{ e0, e1, e2 }
    {	    
    }

    double x() const { return e[0]; }
    double y() const { return e[1]; }
    double z() const { return e[2]; }

    Vec3 operator-() const
    {
	    return Vec3(-e[0], -e[1], -e[2]);
    }
	
    double operator[](int i) const
    {
	    return e[i];
    }
	
    double& operator[](int i)
    {
	    return e[i];
    }

    Vec3& operator+=(const Vec3& v)
	{
        e[0] += v.e[0];
        e[1] += v.e[1];
        e[2] += v.e[2];
        return *this;
    }

    Vec3& operator*=(const double t)
	{
        e[0] *= t;
        e[1] *= t;
        e[2] *= t;
        return *this;
    }

    Vec3& operator/=(const double t)
	{
        return *this *= 1 / t;
    }

    double Length() const
	{
        return sqrt(LengthSquared());
    }

    double LengthSquared() const
	{
        return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
    }

    bool IsNearZero() const
	{
        // Return true if the vector is close to zero in all dimensions.
        const auto s = 1e-8;
        return (fabs(e[0]) < s) && (fabs(e[1]) < s) && (fabs(e[2]) < s);
    }
};

// Type aliases for Vec3
using Point3 = Vec3;   // 3D point
using Color  = Vec3;    // RGB color

// Vec3 Utility Functions

inline std::ostream& operator<<(std::ostream& out, const Vec3& v)
{
    return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

inline Vec3 operator+(const Vec3& u, const Vec3& v)
{
    return Vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

inline Vec3 operator-(const Vec3& u, const Vec3& v)
{
    return Vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

inline Vec3 operator*(const Vec3& u, const Vec3& v)
{
    return Vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

inline Vec3 operator*(double t, const Vec3& v)
{
    return Vec3(t * v.e[0], t * v.e[1], t * v.e[2]);
}

inline Vec3 operator*(const Vec3& v, double t)
{
    return t * v;
}

inline Vec3 operator/(Vec3 v, double t)
{
    return (1 / t) * v;
}

inline double Dot(const Vec3& u, const Vec3& v)
{
    return u.e[0] * v.e[0]
        + u.e[1] * v.e[1]
        + u.e[2] * v.e[2];
}

inline Vec3 Cross(const Vec3& u, const Vec3& v)
{
    return Vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
        u.e[2] * v.e[0] - u.e[0] * v.e[2],
        u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

inline Vec3 UnitVector(Vec3 v)
{
    return v / v.Length();
}

inline Vec3 RandomVec3()
{
    return Vec3(UsefulFunctions::RandomDouble(), 
                UsefulFunctions::RandomDouble(), 
                UsefulFunctions::RandomDouble());
}

inline Vec3 RandomVec3(double min, double max)
{
    return Vec3(UsefulFunctions::RandomDouble(min, max), 
                UsefulFunctions::RandomDouble(min, max), 
                UsefulFunctions::RandomDouble(min, max));
}

inline Vec3 RandomVec3InUnitSphere()
{
    while (true)
    {
        auto p = RandomVec3(-1, 1);
        if (p.LengthSquared() >= 1) continue;
        return p;
    }
}

inline Vec3 RandomUnitVector()
{
    return UnitVector(RandomVec3InUnitSphere());
}

inline Vec3 RandomVec3InHemisphere(const Vec3& normal)
{
    Vec3 in_unit_sphere = RandomVec3InUnitSphere();
    if (Dot(in_unit_sphere, normal) > 0.0) // In the same hemisphere as the normal
    {
        return in_unit_sphere;
    }

    return -in_unit_sphere;
}

inline Vec3 Reflect(const Vec3& v, const Vec3& n) 
{
    return v - 2 * Dot(v, n) * n;
}

inline Vec3 Refract(const Vec3& uv, const Vec3& n, double etai_over_etat) 
{
    // www.scratchapixel.com/lessons/3d-basic-rendering/introduction-to-shading/reflection-refraction-fresnel
    /*double cosi = UsefulFunctions::Clamp(-1, 1, Dot(uv, n));
    double etai = 1;
    double etat = 1.0 / etai_over_etat;
    Vec3 new_n = n;
    if (cosi < 0) 
    { 
        cosi = -cosi; 
    }
    else 
    { 
        std::swap(etai, etat); 
        new_n = -n;
    }
    double eta = etai / etat;
    double k = 1 - eta * eta * (1 - cosi * cosi);
    return k < 0 ? Vec3() : uv * eta + (eta * cosi - sqrt(k)) * new_n;*/
    
    // Peter Shirley
    auto cos_theta = fmin(Dot(-uv, n), 1.0);
    Vec3 r_out_perp = etai_over_etat * (uv + cos_theta * n);
    Vec3 r_out_parallel = -sqrt(abs(1.0 - r_out_perp.LengthSquared())) * n;
    return r_out_perp + r_out_parallel;
}

#endif