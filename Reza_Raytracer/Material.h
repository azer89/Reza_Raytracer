#ifndef __MATERIAL_H__
#define __MATERIAL_H__

#include "UsefulThings.h"

struct HitRecord;

class Material
{
public:

	// pure virtual
    virtual bool Scatter(const Ray3& r_in,
						 const HitRecord& rec, 
						 Color& attenuation, 
						 Ray3& scattered ) const = 0;
};

class Lambertian : public Material
{
public:
    Lambertian(const Color& a) : albedo(a)
    {	    
    }

    virtual bool Scatter(const Ray3& r_in, 
						 const HitRecord& rec, 
						 Color& attenuation, 
						 Ray3& scattered) const override
	{
        //Point3 scatter_direction = rec.p + RandomVec3InHemisphere(rec.normal);
        //Point3 scatter_direction = rec.p + rec.normal + RandomUnitVector();    	
        Point3 scatter_direction = rec.normal + RandomUnitVector();

        // Catch degenerate scatter direction
        if (scatter_direction.IsNearZero())
        {
            scatter_direction = rec.normal;
        }
    	
        scattered = Ray3(rec.p, scatter_direction);
        attenuation = albedo;
        return true;
    }

public:
    Color albedo;
};

#endif