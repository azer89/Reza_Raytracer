A raytracing demo that models the path of individual rays of light as they travel through a virtual 3D scene, calculating how they reflect, refract, and interact with surfaces and materials to produce realistic lighting and shadows. 

### Features

* Lambertian (matte), metal, dielectric (glass) materials.
* CPU Multithreading. Each thread is responsible to calculate rows of pixels
* Bounded Volume Hierarchy (BVH) for faster ray intersections.
* Triangle mesh rendering.
* Wavefront OBJ parser that supports vertex positions, normal vectors, and texture coordinates.
* Surface normal interpolation using barycentric coordinate.
* XML for creating scenes and specifying parameters 

### Pictures 
<div align="center">

 A glass/dielectric dragon showing light refraction</br>
<img width="600" src="https://github.com/azer89/Reza_Raytracer/assets/790432/2c583aa5-ba79-4f74-a8cf-1d8abfe00012">

Bunnies with metal and lambertian material </br>
![bunnies](https://github.com/azer89/Reza_Raytracer/assets/790432/24ebdc7c-2337-44b4-9ad9-54ef2378e41b)

Bunnies with a red metal material </br>
[<img src="https://raw.githubusercontent.com/azer89/Reza_Raytracer/master/results/three_bunnies_600.png">](https://raw.githubusercontent.com/azer89/Reza_Raytracer/master/results/three_bunnies.png)

Another dragon </br>
[<img src="https://raw.githubusercontent.com/azer89/Reza_Raytracer/master/results/metal_dragon_600.png">](https://raw.githubusercontent.com/azer89/Reza_Raytracer/master/results/metal_dragon.png)

Metal spheres </br>
[<img src="https://raw.githubusercontent.com/azer89/Reza_Raytracer/master/results/three_spheres_600.png">](https://raw.githubusercontent.com/azer89/Reza_Raytracer/master/results/three_spheres.png)
</div>

### References
* [_Ray Tracing in One Weekend_](https://raytracing.github.io/books/RayTracingInOneWeekend.html)
* [_Ray Tracing: The Next Week_](https://raytracing.github.io/books/RayTracingTheNextWeek.html)
* [_Ray Tracing: Rendering a Triangle_](https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-rendering-a-triangle)

This app was developed using C++20 and Visual Studio 2020 x64.
Included dependencies are [tinyxml2](https://github.com/leethomason/tinyxml2) and [stb](https://github.com/nothings/stb). 
