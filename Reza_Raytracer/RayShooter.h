#ifndef __RAY_SHOOTER_H__
#define __RAY_SHOOTER_H__

#include <memory>

#include "ImageHandler.h"
#include "HittableList.h"
#include "Camera.h"

class RayShooter
{
private:
	std::unique_ptr<Camera> camera;
	std::unique_ptr<ImageHandler> imgHandler;
	std::unique_ptr<HittableList> world;

	int image_width;
	int image_height;
	int samples_per_pixel; 
	double scale;
	int max_depth; 

public:
	RayShooter();
	~RayShooter();

	void ShootRays();
	void ShootRaysNormalOnly();

private:
	Color RayColor(const Ray3& r, int depth);
	Color RayColorNormalOnly(const Ray3& r);
	Color RayColorWithLightSource(const Ray3& r, const Color& background, const HittableList& world, int depth);
	

};

#endif