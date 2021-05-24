

#include "RayShooter.h"


#include "Material.h"
#include "UsefulThings.h"
#include "XMLParameters.h"

using namespace std;

RayShooter::RayShooter()
{
	// XML
	XMLParameters xml_params;
	xml_params.LoadParametersFromXML();

	// Camera
	camera = std::make_unique<Camera>();

	// renderer setting
	this->image_width = XMLParameters::renderer_image_width;
	this->image_height = static_cast<int>(this->image_width / camera->GetAspectRatio());
	this->samples_per_pixel = XMLParameters::renderer_samples_per_pixel;
	this->scale = 1.0 / samples_per_pixel;
	this->max_depth = XMLParameters::renderer_max_depth;

	// Image IO
	imgHandler = make_unique<ImageHandler>(image_width, image_height); // set up image handler

	 // World
	world = make_unique<HittableList>();
	world->CreateWorld();
}

RayShooter::~RayShooter()
{
}



void RayShooter::ShootRays()
{
	for (int y = image_height - 1; y >= 0; --y)
	{
		// adding progress text
		std::cout << "\rScanlines remaining: " << y << ' ' << std::flush;

		for (int x = 0; x < image_width; ++x)
		{
			Color pixel_color(0, 0, 0);
			for (int s = 0; s < samples_per_pixel; s++)
			{
				auto u = (double(x) + RandomDouble()) / (image_width - 1);
				auto v = (double(y) + RandomDouble()) / (image_height - 1);
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

	std::cout << "\ndone :)\n";
}



// This is a recursive function
Color RayShooter::RayColor(const Ray3& r, int depth)
{
	// If we've exceeded the ray bounce limit, no more light is gathered.
	if (depth <= 0)
	{
		return Color(0, 0, 0);
	}

	// Recursive
	HitRecord rec;
	// t_min = 0.001 is used to remove shadow acne
	if (world->Hit(r, 0.001, infinity, rec))
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
			return attenuation * RayColor(scattered, depth - 1);
			//return emitted + attenuation * RayColor(scattered, world, depth - 1); // does not work
		}
		

		return Color(0, 0, 0);
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
Color RayShooter::RayColorWithLightSource(const Ray3& r, const Color& background, const HittableList& world, int depth)
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

// for debugging normal vectors only
void RayShooter::ShootRaysNormalOnly()
{
	for (int y = image_height - 1; y >= 0; --y)
	{
		std::cout << "\rScanlines remaining: " << y << ' ' << std::flush;

		for (int x = 0; x < image_width; ++x)
		{
			auto u = (double(x) + RandomDouble()) / (image_width - 1);
			auto v = (double(y) + RandomDouble()) / (image_height - 1);
			Ray3 r = camera->GetRay(u, v);
			Color pixel_color = RayColorNormalOnly(r);

			imgHandler->SetPixel(pixel_color.x(),
				pixel_color.y(),
				pixel_color.z(),
				x,
				y);
		}
	}

	imgHandler->WriteToPNG("C://Users//azer//workspace//Reza_Raytracer//render.png");

	std::cout << "\ndone :)\n";
}

// for debugging normal vectors only
Color RayShooter::RayColorNormalOnly(const Ray3& r)
{
	HitRecord rec;
	if (world->Hit(r, 0.001, infinity, rec))
	{
		Vec3 N = UnitVector(rec.normal);
		return 0.5 * Color(N.x() + 1, N.y() + 1, N.z() + 1);
	}

	Vec3 unit_direction = UnitVector(r.Direction());
	auto t = 0.5 * (unit_direction.y() + 1.0);
	return (1.0 - t) * Color(1.0, 1.0, 1.0) + t * Color(0.5, 0.7, 1.0);
}