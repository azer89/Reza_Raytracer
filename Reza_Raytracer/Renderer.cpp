#include "Renderer.h"
#include "ImageHandler.h"
#include "Camera.h"
#include "Material.h"
#include "UsefulThings.h"
#include "XMLParser.h"
#include "GlobalParameters.h"

#include <iostream>
#include <algorithm>
#include <future>

using namespace std;

Renderer::Renderer()
{
	// XML
	XMLParser xml_parser;
	xml_parser.LoadParametersFromXML();

	// Camera
	camera = std::make_unique<Camera>();

	// renderer setting
	this->image_width		= GlobalParameters::renderer_image_width;
	this->image_height		= static_cast<int>(this->image_width / camera->GetAspectRatio());
	this->samples_per_pixel = GlobalParameters::renderer_samples_per_pixel;
	this->scale				= 1.0 / samples_per_pixel;
	this->max_depth			= GlobalParameters::renderer_max_depth;

	// Image IO
	imgHandler = make_unique<ImageHandler>(image_width, image_height); // set up image handler

	 // World
	scene = make_unique<Scene>();
	scene->CreateScene();
}

Renderer::~Renderer()
{
}

/*
Source
	www.cplusplus.com/forum/beginner/240592/
	solarianprogrammer.com/2012/10/17/cpp-11-async-tutorial/
*/
void Renderer::ShootRaysMultithread()
{
	// set up number of thread
	int num_thread = GlobalParameters::num_thread;
	if (num_thread < 1)
	{
		num_thread = std::thread::hardware_concurrency() - 1;
	}

	// nice trick for a fast ceiling
	int num_rows_per_thread = image_height / num_thread + (image_height % num_thread != 0);

	std::cout << "Multi thread raytracing\n";
	std::cout << "Number of threads = " << num_thread << '\n';
	auto start1 = std::chrono::steady_clock::now();

	vector<atomic<int>>  counter_atoms(num_thread);
	vector<future<void>> futures(num_thread);

	for (size_t i = 0; i < num_thread; i++)
	{
		int y_start = i * num_rows_per_thread;
		int y_end = y_start + num_rows_per_thread - 1;
		if (y_end >= image_height) { y_end = image_height - 1; }

		futures.emplace_back(
			std::async(
				std::launch::async,
				&Renderer::ShootRaysByAThread,
				this,
				std::ref(counter_atoms[i]),
				y_start,
				y_end
			)
		);
	}

	// keep looping until all image rows are rendered
	int sum_rows = 0;
	while(sum_rows < image_height)
	{
		// update every 0.5 seconds
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		//std::unique_lock<std::mutex> lock(mutex_task);
		//cv_task.wait(lock);

		sum_rows = 0;
		for (const auto& ca : counter_atoms)
		{
			sum_rows += ca.load();
		}

		// print progress
		std::cout << "\rRows processsed = " << sum_rows << '/' << image_height << std::flush;
	}

	auto end1 = std::chrono::steady_clock::now();
	std::cout << "\nRendering done in " << std::chrono::duration_cast<std::chrono::seconds>(end1 - start1).count() << " s\n\n";

	// save a nice picture
	imgHandler->WriteToPNG("C://Users//azer//workspace//Reza_Raytracer//render.png");
}

void Renderer::ShootRaysByAThread(atomic<int>& counter_atom,
									int y_start, 
									int y_end)
{
	counter_atom = 0;

	for (int y = y_end; y >= y_start; --y)
	{
		for (int x = 0; x < image_width; ++x)
		{
			Color pixel_color(0, 0, 0);
			for (size_t s = 0; s < samples_per_pixel; s++)
			{
				auto u = (double(x) + UsefulFunctions::RandomDouble()) / (image_width - 1);
				auto v = (double(y) + UsefulFunctions::RandomDouble()) / (image_height - 1);
				Ray3 r = camera->GetRay(u, v);
				pixel_color += RayColor(r, max_depth); // recursive function
				//pixel_color += RayColorNormalOnly(r);
			}

			// Divide the color by the number of samples and gamma-correct for gamma=2.0.
			imgHandler->SetPixel(sqrt(pixel_color.x() * scale),
					sqrt(pixel_color.y() * scale),
					sqrt(pixel_color.z() * scale),
					x,
					y);
			// notify main thread that we have computed a pixel
			//cv_task.notify_one();
		}

		// atomic increment that's slower than regular int but whatever
		counter_atom++;
	}
}

void Renderer::ShootRaysSingleThread()
{
	std::cout << "Single thread raytracing\n";

	for (int y = image_height - 1; y >= 0; --y)
	{
		// adding progress text
		std::cout << "\rScanlines remaining: " << y << ' ' << std::flush;

		for (int x = 0; x < image_width; x++)
		{
			Color pixel_color(0, 0, 0);
			for (size_t s = 0; s < samples_per_pixel; s++)
			{
				auto u = (double(x) + UsefulFunctions::RandomDouble()) / (image_width - 1);
				auto v = (double(y) + UsefulFunctions::RandomDouble()) / (image_height - 1);
				Ray3 r = camera->GetRay(u, v);
				pixel_color += RayColor(r, max_depth); // recursive function
			}

			// Divide the color by the number of samples and gamma-correct for gamma=2.0.
			imgHandler->SetPixel(sqrt(pixel_color.x() * scale),
								sqrt(pixel_color.y() * scale),
								sqrt(pixel_color.z() * scale),
								x,
								y);
		}
	}

	imgHandler->WriteToPNG("C://Users//azer//workspace//Reza_Raytracer//render.png");

	std::cout << "\nDone :)\n";
}

// This is a recursive function
Color Renderer::RayColor(const Ray3& r, int depth)
{
	// If we've exceeded the ray bounce limit, no more light is gathered.
	if (depth <= 0)
	{
		return Color(0, 0, 0);
	}

	// Recursive
	HitRecord rec;
	// t_min = 0.001 is used to remove shadow acne
	if (scene->Hit(r, 0.001, UsefulConstants::infinity, rec))
	{
		Ray3 scattered;
		Color attenuation;
		//Color emitted = rec.mat_ptr->Emitted(rec.u, rec.v, rec.p); 

		if (rec.mat_ptr->Scatter(r, rec, attenuation, scattered))
		{
			return attenuation * RayColor(scattered, depth - 1);
			//return emitted + attenuation * RayColor(scattered, world, depth - 1); // work in progress
		}

		return Color(0, 0, 0);
	}

	Vec3 unit_direction = UnitVector(r.Direction());
	auto t = 0.5 * (unit_direction.y() + 1.0);
	return (1.0 - t) * GlobalParameters::back_color1 + t * GlobalParameters::back_color2;
}

// This is a recursive function
Color Renderer::RayColorWithLightSource(const Ray3& r, const Color& background, const Scene& scene, int depth)
{
	// If we've exceeded the ray bounce limit, no more light is gathered.
	if (depth <= 0)
	{
		return Color(0, 0, 0);
	}

	// Recursive
	HitRecord rec;

	// If the ray hits nothing, return the background color.
	if (!scene.Hit(r, 0.001, UsefulConstants::infinity, rec))
	{
		return background;
	}

	Ray3 scattered;
	Color attenuation;
	Color emitted = rec.mat_ptr->Emitted(rec.u, rec.v, rec.p);

	if (!rec.mat_ptr->Scatter(r, rec, attenuation, scattered))
	{
		return emitted;
	}

	return emitted + attenuation * RayColorWithLightSource(scattered, background, scene, depth - 1);
}

// for debugging normal vectors only
Color Renderer::RayColorNormalOnly(const Ray3& r)
{
	HitRecord rec;
	if (scene->Hit(r, 0.001, UsefulConstants::infinity, rec))
	{
		Vec3 normal = UnitVector(rec.normal);
		return 0.5 * Color(normal.x() + 1, normal.y() + 1, normal.z() + 1);
	}

	Vec3 unit_direction = UnitVector(r.Direction());
	auto t = 0.5 * (unit_direction.y() + 1.0);
	return (1.0 - t) * GlobalParameters::back_color1 + t * GlobalParameters::back_color2;
}

