#ifndef __PI_ESTIMATOR_H__
#define __PI_ESTIMATOR_H__

#include "UsefulThings.h"

class PIEstimator
{
	static void Calculate()
	{
		int inside_circle = 0;
		int inside_circle_stratified = 0;
		int sqrt_N = 10000;

        for (int i = 0; i < sqrt_N; i++) 
        {
            for (int j = 0; j < sqrt_N; j++) 
            {
                auto x = UsefulFunct::RandomDouble(-1, 1);
                auto y = UsefulFunct::RandomDouble(-1, 1);
                if (x * x + y * y < 1)
                {
                    inside_circle++;
                }
                x = 2 * ((i + UsefulFunct::RandomDouble()) / sqrt_N) - 1;
                y = 2 * ((j + UsefulFunct::RandomDouble()) / sqrt_N) - 1;
                if (x * x + y * y < 1)
                {
                    inside_circle_stratified++;
                }
            }
        }
	}
};

#endif
