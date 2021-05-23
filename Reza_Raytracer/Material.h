#ifndef __MATERIAL_H__
#define __MATERIAL_H__

#include "UsefulThings.h"
#include "Texture.h"

struct HitRecord;

class Material
{
public:

	// pure virtual
    virtual bool Scatter(const Ray3& r_in,
						 const HitRecord& rec, 
						 Color& attenuation, 
						 Ray3& scattered ) const = 0;

	// For light source or a texture, see derived classes
    virtual Color Emitted(double u, double v, const Point3& p) const
	{
        return Color(0, 0, 0);
    }
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

class Metal : public Material 
{
public:
    Metal(const Color& a) : albedo(a) 
    {
    }

    virtual bool Scatter(const Ray3& r_in, 
                         const HitRecord& rec, 
                         Color& attenuation, 
                         Ray3& scattered
    ) const override 
    {
        Vec3 reflected = Reflect(UnitVector(r_in.Direction()), rec.normal);
        scattered = Ray3(rec.p, reflected);
        attenuation = albedo;

        // if dot product is zero then the vectors are perpendicular
        return (Dot(scattered.Direction(), rec.normal) > 0);
    }

public:
    Color albedo;
};

class DiffuseLight : public Material
{
public:
    DiffuseLight(const Color& c) 
    {
        emit = make_shared<SolidColor>(c);
    }

    virtual bool Scatter(const Ray3& r_in,
        const HitRecord& rec,
        Color& attenuation,
        Ray3& scattered) const override
    {
        return false;
    }

    virtual Color Emitted(double u, double v, const Point3& p) const override
	{        
    	return emit->Value(u, v, p);
    }


public:
    shared_ptr<Texture> emit;

};

#endif