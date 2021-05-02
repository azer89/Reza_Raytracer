

#include <iostream>

#include "ImageHandler.h"
#include "UsefulThings.h"
#include "HittableList.h"
#include "Sphere.h"
#include "Camera.h"


Color RayColor(const Ray3& r, const HittableList& world)
{
	HitRecord rec;
	if (world.Hit(r, 0, infinity, rec)) 
	{
		return 0.5 * (rec.normal + Color(1, 1, 1));
	}
	
	Vec3 unit_direction = UnitVector(r.Direction());
	auto t = 0.5 * (unit_direction.y() + 1.0);
	return (1.0 - t) * Color(1.0, 1.0, 1.0) + t * Color(0.5, 0.7, 1.0);
}

int main()
{
	// Camera
	Camera camera;
	const int samples_per_pixel = 10;
	auto scale = 1.0 / samples_per_pixel;
	
	// Image
	const int image_width = 600;
	const int image_height = static_cast<int>(image_width / camera.GetAspectRatio());
	ImageHandler imgHandler(image_width, image_height); // set up image handler

	 // World
	HittableList world;
	world.CreateWorld();

	for (int y = image_height - 1; y >= 0; --y)
	{
		// adding progress text
		std::cout << "\rScanlines remaining: " << y << ' ' << std::flush;
		
		for (int x = 0; x < image_width; ++x)
		{
			Color pixel_color(0, 0, 0);
			for(int s = 0; s < samples_per_pixel; s++)
			{
				auto u = (double(x) + RandomDouble()) / (image_width - 1);
				auto v = (double(y) + RandomDouble()) / (image_height - 1);
				Ray3 r = camera.GetRay(u, v);
				pixel_color += RayColor(r, world);
			}
			imgHandler.SetPixel(pixel_color.x() * scale, 
								pixel_color.y() * scale,
								pixel_color.z() * scale);
		}
	}

	imgHandler.WriteToPNG("C://Users//azer//workspace//Reza_Raytracer//render.png");
	//STBWrapper::WriteToPNG("C://Users//azer//workspace//Reza_Raytracer//render.png", pixels, width, height);

	return 0;
}