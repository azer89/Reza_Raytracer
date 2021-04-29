
/*#include <iostream>
#include <vector>
#include <fstream> // ofstream


#include "Vec3.h"
#include "STBWrapper.h"*/

#include <iostream>
#include <fstream>
#include <sstream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STBI_MSC_SECURE_CRT
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

int main()
{
	const int width = 200;
	const int height = 200;
	int channel_num = 3;
	
//#define CHANNEL_NUM 3
	
	uint8_t* pixels = new uint8_t[width * height * channel_num];

	int index = 0;
	for (int j = height - 1; j >= 0; --j)
	{
		for (int i = 0; i < width; ++i)
		{
			float r = (float)i / (float)width;
			float g = (float)j / (float)height;
			float b = 0.2f;
			int ir = int(255.99 * r);
			int ig = int(255.99 * g);
			int ib = int(255.99 * b);

			pixels[index++] = ir;
			pixels[index++] = ig;
			pixels[index++] = ib;
		}
	}

	// if CHANNEL_NUM is 4, you can use alpha channel in png
	stbi_write_png("test.png", width, height, channel_num, pixels, width * channel_num);

	// You have to use 3 comp for complete jpg file. If not, the image will be grayscale or nothing.
	//stbi_write_jpg("stbjpg3.jpg", width, height, 3, pixels, 100);
	delete[] pixels;

	return 0;
}

//int main_didntwork()
//{
//	using namespace std;
//
//	const int img_width = 256;
//	const int img_height = 256;
//
//	// Render
//	//ofstream my_file;
//	//my_file.open("image.ppm");
//
//	//my_file << "P3\n" << img_width << ' ' << img_height << "\n255\n";
//	//std::vector<int> data(img_width * img_height * 3);
//	uint8_t* data = new uint8_t[img_width * img_height * 3];
//	int i = 0;
//	
//	for(int y = img_height - 1; y >= 0; y--)
//	{
//		std::cout << "\rScanlines remaining: " << y << ' ' << std::flush;
//		for (int x = 0; x < img_width; x++)
//		{
//			auto r = double(x) / (img_width - 1);
//			auto g = double(y) / (img_height - 1);
//			auto b = 0.25;
//
//			//int ir = static_cast<int>(255.0 * r);
//			//int ig = static_cast<int>(255.0 * g);
//			//int ib = static_cast<int>(255.0 * b);
//			data[i++] = int(255.0 * r);
//			data[i++] = int(255.0 * g);
//			data[i++] = int(255.0 * b);
//
//			//my_file << ir << ' ' << ig << ' ' << ib << '\n';
//		}
//	}
//
//	STBWrapper::WriteToPNG("render.png", data, img_width, img_height);
//
//	delete[] data;
//	
//	//my_file.close();
//
//	// http://chanhaeng.blogspot.com/2018/12/how-to-use-stbimagewrite.html
//	
//	//cout << "Hello World\n";
//
//	/*ofstream myfile;
//	myfile.open("example.txt");
//	myfile << "Writing this to a file.\n";
//	myfile << "Writing this to a file.\n";
//	myfile << "Writing this to a file.\n";
//	myfile << "Writing this to a file.\n";
//	myfile.close();*/
//	
//	return 0;
//}