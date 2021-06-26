#include <iostream>
#include <memory>

#include "RayShooter.h"
#include "GlobalParameters.h"

int main()
{
	RayShooter rShooter;

	if (GlobalParameters::num_thread > 1)
	{
		rShooter.ShootRaysMultithread();
	}
	else
	{
		rShooter.ShootRaysSingleThread(); 
	}

	std::cin.get();

	return 0;
}