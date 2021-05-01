

#include <iostream>

#include "ImageHandler.h"

int main()
{
	const int width  = 512;
	const int height = 512;
	int channel_num = 3;
	ImageHandler imgHandler(width, height);
	
	//uint8_t* pixels = new uint8_t[width * height * channel_num];

	int index = 0;
	for (int y = height - 1; y >= 0; --y)
	{
		// adding progress text
		std::cout << "\rScanlines remaining: " << y << ' ' << std::flush;
		
		for (int x = 0; x < width; ++x)
		{
			auto r = double(x) / (width - 1);
			auto g = double(y) / (height - 1);
			auto b = 0.25;

			imgHandler.SetPixel(r, g, b);
			/*pixels[index++] = static_cast<int>(255.0 * r);
			pixels[index++] = static_cast<int>(255.0 * g);
			pixels[index++] = static_cast<int>(255.0 * b);*/
		}
	}

	imgHandler.WriteToPNG("C://Users//azer//workspace//Reza_Raytracer//render.png");
	//STBWrapper::WriteToPNG("C://Users//azer//workspace//Reza_Raytracer//render.png", pixels, width, height);

	//delete[] pixels;

	return 0;
}