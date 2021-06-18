#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include "Vec3.h"

class Texture
{
public:
    virtual Color Value(double u, double v, const Point3& p) const = 0;
};

class SolidColorTexture : public Texture 
{
public:
    SolidColorTexture()
    {	    
    }
	
    SolidColorTexture(Color c) : color_value(c)
    {	    
    }

    SolidColorTexture(double red, double green, double blue)
        : SolidColorTexture(Color(red, green, blue)) {}

    virtual Color Value(double u, double v, const Vec3& p) const override
	{
        return color_value;
    }

private:
    Color color_value;
};

class CheckerTexture : public Texture 
{
public:
    CheckerTexture() {}

    CheckerTexture(shared_ptr<Texture> _even, shared_ptr<Texture> _odd)
        : even(_even), odd(_odd) {}

    CheckerTexture(Color c1, Color c2)
        : even(make_shared<SolidColorTexture>(c1)), odd(make_shared<SolidColorTexture>(c2)) 
    {
    }

    virtual Color Value(double u, double v, const Point3& p) const override 
    {
        auto sines = sin(40 * p.x()) * sin(40 * p.y()) * sin(40 * p.z());
        if (sines < 0)
        {
            return odd->Value(u, v, p);
        }
        else
        {
            return even->Value(u, v, p);
        }
    }

public:
    shared_ptr<Texture> odd;
    shared_ptr<Texture> even;
};

#endif
