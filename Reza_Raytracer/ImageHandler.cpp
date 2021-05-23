
#include "ImageHandler.h"
#include "UsefulThings.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STBI_MSC_SECURE_CRT
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

ImageHandler::ImageHandler(int img_width, int img_height)
{
	this->img_width = img_width;
	this->img_height = img_height;
	this->num_channel = 3; // 4 if you want alpha
	
	this->pixels = std::make_unique<uint8_t[]>(this->img_width * this->img_height * this->num_channel);
	//pixels = new uint8_t[img_width * img_height * num_channel];
	this->pixel_iterator = 0;
}

ImageHandler::~ImageHandler()
{
}

// new, parallelizable
void ImageHandler::SetPixel(double r, double g, double b, int x, int y)
{
	r = Clamp(r, 0.0, 0.999);
	g = Clamp(g, 0.0, 0.999);
	b = Clamp(b, 0.0, 0.999);

	y = img_height - y - 1;
	int index = (x + (y * img_width)) * num_channel;

	pixels[index]	  = static_cast<uint8_t>(255.0 * r);
	pixels[index + 1] = static_cast<uint8_t>(255.0 * g);
	pixels[index + 2] = static_cast<uint8_t>(255.0 * b);
}

// old, don't use this
void ImageHandler::SetPixel(double r, double g, double b)
{
	r = Clamp(r, 0.0, 0.999);
	g = Clamp(g, 0.0, 0.999);
	b = Clamp(b, 0.0, 0.999);
	
	pixels[pixel_iterator++] = static_cast<uint8_t>(255.0 * r);
	pixels[pixel_iterator++] = static_cast<uint8_t>(255.0 * g);
	pixels[pixel_iterator++] = static_cast<uint8_t>(255.0 * b);
}

// STB
void ImageHandler::WriteToPNG(const std::string& filename)
{
	stbi_write_png(filename.c_str(), 
		img_width,
		img_height,
		num_channel,
		pixels.get(), 
		img_width * num_channel);
}



