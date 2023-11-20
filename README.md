A raytracing app that models the path of individual rays of light as they travel through a virtual 3D environment, calculating how they reflect, refract, and interact with surfaces and materials to produce lifelike lighting and shadows. 

### Features

* Lambertian, metal, dielectric, light source materials
* Triangle mesh rendering
* Smooth surface normals using barycentric interpolation
* XML for creating scenes and specifying parameters 
* Bounded Volume Hierarchy
* Wavefront OBJ parser that supports vertex positions, normal vectors, and texture coordinates.
* CPU Multithreading

### Pictures 
<div align="center">

<img width="400" src="https://github.com/azer89/Reza_Raytracer/assets/790432/8b12c0c2-9815-4d15-9afa-e853df42ad24">

![bunnies](https://github.com/azer89/Reza_Raytracer/assets/790432/24ebdc7c-2337-44b4-9ad9-54ef2378e41b)

[<img src="https://raw.githubusercontent.com/azer89/Reza_Raytracer/master/results/three_bunnies_600.png">](https://raw.githubusercontent.com/azer89/Reza_Raytracer/master/results/three_bunnies.png)

[<img src="https://raw.githubusercontent.com/azer89/Reza_Raytracer/master/results/metal_dragon_600.png">](https://raw.githubusercontent.com/azer89/Reza_Raytracer/master/results/metal_dragon.png)

[<img src="https://raw.githubusercontent.com/azer89/Reza_Raytracer/master/results/three_spheres_600.png">](https://raw.githubusercontent.com/azer89/Reza_Raytracer/master/results/three_spheres.png)
</div>

### References
* [_Ray Tracing in One Weekend_](https://raytracing.github.io/books/RayTracingInOneWeekend.html)
* [_Ray Tracing: The Next Week_](https://raytracing.github.io/books/RayTracingTheNextWeek.html)
* [_Ray Tracing: Rendering a Triangle_](https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-rendering-a-triangle)

This app was developed using C++14 and Visual Studio 2019.
Included dependencies are [tinyxml2](https://github.com/leethomason/tinyxml2) and [stb](https://github.com/nothings/stb). 
