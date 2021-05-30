

#include <iostream>
#include <memory>

#include "RayShooter.h"

int main()
{
	RayShooter rShooter;

	rShooter.ShootRaysMultithreadAsync();
	//rShooter.ShootRays();


	std::cin.get();

	return 0;
}