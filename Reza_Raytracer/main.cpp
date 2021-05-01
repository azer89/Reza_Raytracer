

#include <iostream>

#include "ImageHandler.h"
#include "Vec3.h"
#include "Ray3.h"


double RaySphereIntersection(const Point3& center, double radius, const Ray3& r)
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

	// original version
	/*auto a = Dot(r.Direction(), r.Direction());
	auto b = 2.0 * Dot(oc, r.Direction());
	auto c = Dot(oc, oc) - radius * radius;
	auto discriminant = b * b - 4 * a * c;*/

	// improved
	auto a = r.Direction().LengthSquared(); // because r * r = ||r||
	auto half_b = Dot(oc, r.Direction());
	auto c = oc.LengthSquared() - radius * radius;
	auto discriminant = half_b * half_b - a * c;
	
	if(discriminant < 0)
	{
		return -1;
	}

	// original version
	//return (-b - sqrt(discriminant)) / (2.0 * a);
	// improved
	return (-half_b - sqrt(discriminant)) / a;
}

Color RayColor(const Ray3& r)
{
	Point3 sphere_center(0, 0, -1);
	double sphere_radius = 0.5;
	double t = RaySphereIntersection(sphere_center, sphere_radius, r);
	if (t > 0)
	{
		Vec3 normal_vec = UnitVector(r.At(t) - sphere_center);
		return 0.5 * Color(normal_vec.x() + 1, normal_vec.y() + 1, normal_vec.z() + 1);
	}
	
	Vec3 unit_direction = UnitVector(r.Direction());
	t = 0.5 * (unit_direction.y() + 1.0);
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