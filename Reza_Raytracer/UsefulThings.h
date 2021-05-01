#ifndef __USEFUL_THINGS__
#define __USEFUL_THINGS__

#include <cmath>
#include <limits>
#include <memory>


// Usings

using std::shared_ptr;
using std::make_shared;
using std::sqrt;

// Constants

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// Utility Functions

inline double DegreesToRadians(double degrees)
{
    return degrees * pi / 180.0;
}

// Common Headers

#include "Ray3.h"
#include "Vec3.h"

#endif