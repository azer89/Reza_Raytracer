#include <iostream>
#include <memory>

#include "RayShooter.h"

int main()
{
	RayShooter rShooter;

	rShooter.ShootRaysMultithread();
	//rShooter.ShootRays(); // single thread version

	std::cin.get();

	return 0;
}