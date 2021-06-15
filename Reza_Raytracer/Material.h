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

class LambertianMaterial : public Material
{
public:
    LambertianMaterial(const Color& a) : albedo(a)
    {	    
    }

    virtual bool Scatter(const Ray3& r_in, 
						 const HitRecord& rec, 
						 Color& attenuation, 
						 Ray3& scattered) 
        const override
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

class MetalMaterial : public Material 
{
public:
    MetalMaterial(const Color& a, double f) :
        albedo(a),
        fuzzy(f < 1 ? f : 1)
    {
    }

    virtual bool Scatter(const Ray3& r_in, 
                         const HitRecord& rec, 
                         Color& attenuation, 
                         Ray3& scattered ) 
        const override 
    {
        Vec3 reflected = Reflect(UnitVector(r_in.Direction()), UnitVector(rec.normal) );
        scattered = Ray3(rec.p, reflected + fuzzy * RandomVec3InUnitSphere());
        attenuation = albedo;

        // if dot product is zero then the vectors are perpendicular
        return (Dot(scattered.Direction(), rec.normal) > 0);
    }

public:
    Color albedo;
    double fuzzy;
};

class DiffuseLightMaterial : public Material
{
public:
    DiffuseLightMaterial(const Color& c)
    {
        emit = make_shared<SolidColorTexture>(c);
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