#ifndef __RENDERER_H__
#define __RENDERER_H__

#include <memory>
#include <thread> 
#include <atomic>
//#include <condition_variable>
//#include <mutex>

#include "Scene.h"

class ImageHandler;
class Camera;

class Renderer
{
private:
	std::unique_ptr<Camera> camera;
	std::unique_ptr<ImageHandler> imgHandler;
	std::unique_ptr<Scene> scene;

	//std::condition_variable cv_task;
	//std::mutex mutex_task;

	double scale;

	int image_width;
	int image_height;
	int samples_per_pixel; 
	int max_depth; 

public:
	Renderer();
	~Renderer();
			
	// Single thread
	void ShootRaysSingleThread();

	// Multi threads using std::async and std::future
	void ShootRaysMultithread();

	// thread task
	void ShootRaysByAThread(std::atomic<int>& counter_atom, 
			int y_start,
			int y_end);

private:
	Color RayColor(const Ray3& r, int depth);
	Color RayColorNormalOnly(const Ray3& r);
	Color RayColorWithLightSource(const Ray3& r, 
								  const Color& background, 
								  const Scene& scene, int depth);
};

#endif