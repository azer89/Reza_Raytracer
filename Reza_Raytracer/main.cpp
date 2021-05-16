

#include <iostream>

#include "ImageHandler.h"
#include "UsefulThings.h"
#include "HittableList.h"
#include "Sphere.h"
#include "Camera.h"

// This is a recursive function
Color RayColor(const Ray3& r, const HittableList& world, int depth)
{
	// If we've exceeded the ray bounce limit, no more light is gathered.
	if (depth <= 0)
		return Color(0, 0, 0);

	// Recursive
	HitRecord rec;
	// t_min = 0.001 is used to remove shadow acne
	if (world.Hit(r, 0.001, infinity, rec))
	{
		// lighter shadow
		//Point3 target = rec.p + RandomVec3InHemisphere(rec.normal);

		// better shadow
		//Point3 target = rec.p + rec.normal + RandomUnitVector();

		// Recursive
		//return 0.5 * RayColor(Ray3(rec.p, target - rec.p), world, depth - 1);

		Ray3 scattered;
		Color attenuation;
		//Color emitted = rec.mat_ptr->Emitted(rec.u, rec.v, rec.p); 
		
		if (rec.mat_ptr->Scatter(r, rec, attenuation, scattered))
		{
			return attenuation * RayColor(scattered, world, depth - 1);
			//return emitted + attenuation * RayColor(scattered, world, depth - 1); // does not work
		}
		//else
		//{
		//	return emitted;
		//}
	}

	// Non recursive
	/*HitRecord rec;
	if (world.Hit(r, 0, infinity, rec))
	{
		return 0.5 * (rec.normal + Color(1, 1, 1));
	}*/

	Vec3 unit_direction = UnitVector(r.Direction());
	auto t = 0.5 * (unit_direction.y() + 1.0);
	return (1.0 - t) * Color(1.0, 1.0, 1.0) + t * Color(0.5, 0.7, 1.0);
}

// This is a recursive function
Color RayColorWithLightSource(const Ray3& r, const Color& background, const HittableList& world, int depth)
{
	// If we've exceeded the ray bounce limit, no more light is gathered.
	if (depth <= 0)
		return Color(0, 0, 0);

	// Recursive
	HitRecord rec;

	// If the ray hits nothing, return the background color.
	if (!world.Hit(r, 0.001, infinity, rec))
		return background;

	Ray3 scattered;
	Color attenuation;
	Color emitted = rec.mat_ptr->Emitted(rec.u, rec.v, rec.p);

	if (!rec.mat_ptr->Scatter(r, rec, attenuation, scattered))
		return emitted;

	return emitted + attenuation * RayColorWithLightSource(scattered, background, world, depth - 1);
}

int main()
{
	// Camera
	Camera camera;
	
	
	// Image
	const int image_width = 600;
	const int image_height = static_cast<int>(image_width / camera.GetAspectRatio());
	ImageHandler imgHandler(image_width, image_height); // set up image handler
	const int samples_per_pixel = 100; // 100
	auto scale = 1.0 / samples_per_pixel;
	const int max_depth = 50; // 50

	 // World
	HittableList world;
	world.CreateWorld();
	Color background(0, 0, 0);

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
				//pixel_color += RayColorWithLightSource(r, background, world, max_depth); // recursive function
				pixel_color += RayColor(r, world, max_depth); // recursive function
			}

			// Divide the color by the number of samples and gamma-correct for gamma=2.0.
			imgHandler.SetPixel(sqrt(pixel_color.x() * scale), 
								sqrt(pixel_color.y() * scale),
								sqrt(pixel_color.z() * scale));
		}
	}

	imgHandler.WriteToPNG("C://Users//azer//workspace//Reza_Raytracer//render.png");
	//STBWrapper::WriteToPNG("C://Users//azer//workspace//Reza_Raytracer//render.png", pixels, width, height);

	return 0;
}