#include <iostream>
#include <memory>

#include "RayShooter.h"

int main()
{
	RayShooter rShooter;

	rShooter.ShootRaysMultithread();
	//rShooter.ShootRaysSingleThread(); 

	std::cin.get();

	return 0;
}