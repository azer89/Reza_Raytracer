#include <iostream>
#include <memory>

#include "Renderer.h"
#include "GlobalParameters.h"
#include "PIEstimator.h"

int main()
{
	//PIEstimator::Calculate();

	Renderer renderer;

	/*
	if num_thread >  0 the program will use n threads.
	if num_thread =  1 the program will run on a single thread.
	if num_thread <= 0 the program will use max number of logical cpus minus one.
	*/
	if (GlobalParameters::num_thread == 1)
	{
		renderer.ShootRaysSingleThread();
	}
	else
	{
		renderer.ShootRaysMultithread();
	}

	std::cin.get();

	return 0;
}