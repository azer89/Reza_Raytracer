#include <iostream>
#include <memory>

#include "Renderer.h"
#include "GlobalParameters.h"
#include "PIEstimator.h"

int main()
{
	//PIEstimator::Calculate();

	Renderer renderer;

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