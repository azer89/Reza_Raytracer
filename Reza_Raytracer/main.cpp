#include <iostream>
#include <memory>

#include "Renderer.h"
#include "GlobalParameters.h"

int main()
{
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