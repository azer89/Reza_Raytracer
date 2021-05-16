#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include "Vec3.h"

class Texture
{
public:
    virtual Color Value(double u, double v, const Point3& p) const = 0;
};

class SolidColor : public Texture {
public:
    SolidColor()
    {	    
    }
	
    SolidColor(Color c) : color_value(c)
    {	    
    }

    SolidColor(double red, double green, double blue)
        : SolidColor(Color(red, green, blue)) {}

    virtual Color Value(double u, double v, const Vec3& p) const override
	{
        return color_value;
    }

private:
    Color color_value;
};

#endif
