#ifndef __RAY_SHOOTER_H__
#define __RAY_SHOOTER_H__

#include <memory>
#include <thread> // is this needed?
#include <atomic>

#include "HittableList.h"

class ImageHandler;
class Camera;

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
			
	// single thread
	void ShootRaysSingleThread();

	// multi threads
	void ShootRaysMultithread();

	// thread task
	void ShootRaysByAThread(std::atomic<int>& counter_atom, 
			int y_start,
			int y_end);

	// std::thread version
	//void ShootRaysMultithread();

	// for debugging
	void ShootRaysNormalOnly();
	
	// for debugging
	//void ShootRaysInSegment(int row_start, int row_end);
	

private:
	Color RayColor(const Ray3& r, int depth);
	Color RayColorNormalOnly(const Ray3& r);
	Color RayColorWithLightSource(const Ray3& r, 
								  const Color& background, 
								  const HittableList& world, int depth);
};

#endif