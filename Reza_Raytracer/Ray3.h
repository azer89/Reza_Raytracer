#ifndef __RAY_3_H__
#define __RAY_3_H__

#include "Vec3.h"

class Ray3
{
public:
    Point3 origin;
    Vec3 direction;
	
public:
	// Constructor
    Ray3()
    {	    
    }

    // Constructor
    Ray3(const Point3& orig, const Vec3& dir)
        : origin(orig),
		  direction(dir)
    {}

    Point3 Origin() const 
    { 
        return origin; 
    }
	
    Vec3 Direction() const 
    { 
        return direction; 
    }

    // t = [0, 1]
    Point3 At(double t) const
	{
        return origin + t * direction;
    }
};

#endif
