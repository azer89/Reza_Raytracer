#ifndef __RENDERER_H__
#define __RENDERER_H__

#include <memory>
#include <thread> 
#include <atomic>

#include "Scene.h"
#include "ImageHandler.h"
#include "Camera.h"

class Renderer
{
private:
	std::unique_ptr<ImageHandler> img_handler;
	std::unique_ptr<Camera> camera;
	std::unique_ptr<Scene> scene;

	double scale;
	int image_width;
	int image_height;
	int samples_per_pixel;
	int max_depth;

public:
	Renderer();
	//~Renderer();

	// Single thread
	void ShootRaysSingleThread();

	// Multi threads using std::async and std::future
	void ShootRaysMultithread();

	// Thread task
	void ShootRaysByAThread(std::atomic<int>& counter_atom,
		int y_start,
		int y_end);

private:
	// Calculate a color of a ray
	Color RayColor(const Ray3& r, int depth);

	// For debugging normal vectors only
	Color RayColorNormalOnly(const Ray3& r);
};

#endif