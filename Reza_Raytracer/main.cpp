

#include <iostream>

#include "ImageHandler.h"
#include "Vec3.h"
#include "Ray3.h"


bool DoesRayHitSphere(const Point3& center, double radius, const Ray3& r)
{

	/*
	Equation
		b * b t^2 +
		2 b * (A - C) t +
		(A - C) * (A - C) - r^2
		= 0
	where
		t is a scalar
		b is a direction vector
		A is the the ray origin
		C is the center of the sphere
	*/
	
	Vec3 oc = r.Origin() - center;
	auto a = Dot(r.Direction(), r.Direction());
	auto b = 2.0 * Dot(oc, r.Direction());
	auto c = Dot(oc, oc) - radius * radius;
	auto discriminant = b * b - 4 * a * c;
	return (discriminant > 0);
}

Color RayColor(const Ray3& r)
{
	if (DoesRayHitSphere(Point3(0, 0, -1), 0.5, r))
	{
		return Color(1, 0, 0);
	}
	
	Vec3 unit_direction = UnitVector(r.Direction());
	auto t = 0.5 * (unit_direction.y() + 1.0);
	return (1.0 - t) * Color(1.0, 1.0, 1.0) + t * Color(0.5, 0.7, 1.0);
}

int main()
{
	// Image
	const auto aspect_ratio = 16.0 / 9.0;
	const int image_width = 800;
	const int image_height = static_cast<int>(image_width / aspect_ratio);
	ImageHandler imgHandler(image_width, image_height); // set up image handler

	// Camera
	const auto viewport_height = 2.0;
	const auto viewport_width = aspect_ratio * viewport_height;
	const auto focal_length = 1.0;

	const auto origin = Point3(0, 0, 0);
	const auto horizontal = Vec3(viewport_width, 0, 0);
	const auto vertical = Vec3(0, viewport_height, 0);
	const auto lower_left_corner = origin - (horizontal / 2) - (vertical / 2) - Vec3(0, 0, focal_length);
	

	for (int y = image_height - 1; y >= 0; --y)
	{
		// adding progress text
		std::cout << "\rScanlines remaining: " << y << ' ' << std::flush;
		
		for (int x = 0; x < image_width; ++x)
		{
			auto u = double(x) / (image_width - 1);
			auto v = double(y) / (image_height - 1);
			Ray3 r(origin, lower_left_corner + u * horizontal + v * vertical - origin);
			Color pixel_color = RayColor(r);

			imgHandler.SetPixel(pixel_color.x(), pixel_color.y(), pixel_color.z());
		}
	}

	imgHandler.WriteToPNG("C://Users//azer//workspace//Reza_Raytracer//render.png");
	//STBWrapper::WriteToPNG("C://Users//azer//workspace//Reza_Raytracer//render.png", pixels, width, height);

	return 0;
}