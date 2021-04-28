
#ifndef __VEC_3__
#define __VEC_3__

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

};

// Type aliases for Vec3
using Point3 = Vec3;   // 3D point
using Color  = Vec3;    // RGB color

#endif