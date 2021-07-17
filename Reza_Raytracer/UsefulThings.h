#ifndef __USEFUL_THINGS_H__
#define __USEFUL_THINGS_H__

#include <cmath>
#include <limits>
#include <memory>
#include <random>

// Usings

using std::shared_ptr;
using std::make_shared;
using std::sqrt;

// Constants
namespace UsefulConstants
{
    const double epsilon = std::numeric_limits<double>::epsilon();
    const double infinity = std::numeric_limits<double>::infinity();
    const double pi = std::acos(-1);
}

// Utility Functions
namespace UsefulFunctions
{
    inline double RandomDouble()
    {
        static std::uniform_real_distribution<double> distribution(0.0, 1.0);
        static std::mt19937 generator;
        return distribution(generator);
    }

    inline double RandomDouble(double min, double max)
    {
        // Returns a random real in [min,max).
        return min + (max - min) * RandomDouble();
    }

    // Returns a random integer in [min,max]
    inline int RandomInt(int min, int max)
    {
        return static_cast<int>(RandomDouble(min, max + 1));
    }

    inline double DegreesToRadians(double degrees)
    {
        return degrees * UsefulConstants::pi / 180.0;
    }

    inline double Clamp(double x, double min, double max)
    {
        if (x < min) return min;
        if (x > max) return max;
        return x;
    }
}

#endif