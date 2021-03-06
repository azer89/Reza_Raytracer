#ifndef __MATERIAL_H__
#define __MATERIAL_H__

#include "UsefulThings.h"
#include "Texture.h"

#include <iostream>
#include <algorithm>

struct HitRecord;

// github.com/RayTracing/raytracing.github.io/blob/master/src/TheNextWeek/material.h

// Pure virtual class
class Material
{
public:
    virtual bool Scatter(const Ray3& r_in,
                         const HitRecord& rec, 
                         Color& attenuation, 
                         Ray3& scattered ) const = 0; // Causing pure virtual class

	// For light source or a texture, see derived classes
    virtual Color Emitted(double u, double v, const Point3& p) const
    {
        // TODO
        return Color(0, 0, 0);
    }
};

class LambertianMaterial : public Material
{
public:
    LambertianMaterial(const Color& a) : albedo(make_shared<SolidColorTexture>(a)) {}
    LambertianMaterial(shared_ptr<Texture>& t) : albedo(t) {}

    bool Scatter(const Ray3& r_in, 
				 const HitRecord& rec, 
				 Color& attenuation, 
				 Ray3& scattered) 
        const override
	{
        auto scatter_direction = rec.normal + RandomUnitVector();

        // Catch degenerate scatter direction
        if (scatter_direction.IsNearZero())
        {
            scatter_direction = rec.normal;
        }
    	
        scattered = Ray3(rec.p, scatter_direction);
        attenuation = albedo->Value(rec.u, rec.v, rec.p);
        return true;
    }

public:
    // Color;
    shared_ptr<Texture> albedo;
};

// Alternative lambertian material
class LambertianAltMaterial : public Material
{
public:
    LambertianAltMaterial(const Color& a) : albedo(make_shared<SolidColorTexture>(a)) {}
    LambertianAltMaterial(shared_ptr<Texture>& t) : albedo(t) {}

    bool Scatter(const Ray3& r_in,
        const HitRecord& rec,
        Color& attenuation,
        Ray3& scattered)
        const override
    {
        auto scatter_direction = RandomVec3InHemisphere(rec.normal);
        //auto scatter_direction = rec.p + RandomVec3InHemisphere(rec.normal);
        //auto scatter_direction = rec.p + rec.normal + RandomUnitVector();   

        // Catch degenerate scatter direction
        if (scatter_direction.IsNearZero())
        {
            scatter_direction = rec.normal;
        }

        scattered = Ray3(rec.p, scatter_direction);
        attenuation = albedo->Value(rec.u, rec.v, rec.p);
        return true;
    }

public:
    // Color;
    shared_ptr<Texture> albedo;
};

class MetalMaterial : public Material
{
public:
    MetalMaterial(const Color& a, double f) :
        albedo(make_shared<SolidColorTexture>(a)),
        fuzzy(f < 1 ? f : 1)
    {
    }

    MetalMaterial(shared_ptr<Texture>& t, double f) :
        albedo(t),
        fuzzy(f < 1 ? f : 1)
    {
    }

    bool Scatter(const Ray3& r_in,
        const HitRecord& rec,
        Color& attenuation,
        Ray3& scattered)
        const override
    {
        Vec3 reflected = Reflect(UnitVector(r_in.Direction()), UnitVector(rec.normal));
        scattered = Ray3(rec.p, reflected + fuzzy * RandomVec3InUnitSphere());

        attenuation = albedo->Value(rec.u, rec.v, rec.p); // Original

        // if dot product is zero then the vectors are perpendicular
        return (Dot(scattered.Direction(), rec.normal) > 0);
    }

public:
    //Color albedo;
    shared_ptr<Texture> albedo;
    double fuzzy;
};

class ShlickMetalMaterial : public Material 
{
public:
    ShlickMetalMaterial(const Color& a, double f) :
        albedo(make_shared<SolidColorTexture>(a)),
        fuzzy(f < 1 ? f : 1)
    {
    }

    ShlickMetalMaterial(shared_ptr<Texture>& t, double f) :
        albedo(t),
        fuzzy(f < 1 ? f : 1)
    {
    }

    bool Scatter(const Ray3& r_in, 
                 const HitRecord& rec, 
                 Color& attenuation, 
                 Ray3& scattered ) 
        const override 
    {
        Vec3 reflected = Reflect(UnitVector(r_in.Direction()), UnitVector(rec.normal) );
        //Point3 scatter_direction = reflected + fuzzy * RandomVec3InUnitSphere();
        scattered = Ray3(rec.p, reflected + fuzzy * RandomVec3InUnitSphere());

        //attenuation = albedo->Value(rec.u, rec.v, rec.p); // Original

        Vec3 unit_direction = UnitVector(r_in.Direction()); 
        double cos_theta = fmin(Dot(-unit_direction, rec.normal), 1.0);
        attenuation = MetalReflectance(cos_theta, albedo->Value(rec.u, rec.v, rec.p)); // Schlick's approximation

        // if dot product is zero then the vectors are perpendicular
        return (Dot(scattered.Direction(), rec.normal) > 0);
    }

    /*
        Schlick's approximation for metal
        github.com/RayTracing/raytracing.github.io/issues/844
    */
    Color MetalReflectance(double cosine, const Color& albedo) const
    {
        const Color white = Color(1, 1, 1);
        return albedo + (white - albedo) * pow(1 - cosine, 5);
    }

public:
    //Color albedo;
    shared_ptr<Texture> albedo;
    double fuzzy;
};

class DielectricMaterial : public Material 
{
public:
    DielectricMaterial(shared_ptr<Texture> t, double index_of_refraction) : 
        albedo(t),
        ir(index_of_refraction)
    {
    }

    bool Scatter(const Ray3& r_in, 
                 const HitRecord& rec, 
                 Color& attenuation, 
                 Ray3& scattered
    ) const override 
    {
        attenuation = albedo->Value(rec.u, rec.v, rec.p);
        double refraction_ratio = rec.front_face ? (1.0 / ir) : ir;

        Vec3 unit_direction = UnitVector(r_in.Direction());
        double cos_theta = std::min(Dot(-unit_direction, rec.normal), 1.0);
        double sin_theta = sqrt(1.0 - cos_theta * cos_theta);

        bool cannot_refract = refraction_ratio * sin_theta > 1.0;
        Vec3 scatter_direction;

        if (cannot_refract || Reflectance(cos_theta, refraction_ratio) > UsefulFunct::RandomDouble())
        {
            scatter_direction = Reflect(unit_direction, rec.normal);
        }
        else
        {
            scatter_direction = Refract(unit_direction, rec.normal, refraction_ratio);
        }

        scattered = Ray3(rec.p, scatter_direction);
        return true;
    }

private:
    static double Reflectance(double cosine, double ref_idx) 
     {
        // Use Schlick's approximation for reflectance.
        auto r0 = (1 - ref_idx) / (1 + ref_idx);
        r0 = r0 * r0;
        return r0 + (1 - r0) * pow((1 - cosine), 5);
    }

public:
    //Color albedo;
    shared_ptr<Texture> albedo;

    // Index of Refraction
    double ir; 
};

class DiffuseLightMaterial : public Material
{
public:
    DiffuseLightMaterial(shared_ptr<Texture> t)
    {
        emit = t;
    }

    bool Scatter(const Ray3& r_in,
                 const HitRecord& rec,
                 Color& attenuation,
                 Ray3& scattered) const override
    {
        return false;
    }

    // TODO
    Color Emitted(double u, double v, const Point3& p) const override
	{        
    	return emit->Value(u, v, p);
    }

public:
    shared_ptr<Texture> emit;
};

#endif