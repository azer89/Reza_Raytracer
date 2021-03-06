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
}

ImageHandler::~ImageHandler()
{
}

// Parallelizable
void ImageHandler::SetPixel(double r, double g, double b, int x, int y)
{
	r = UsefulFunct::Clamp(r, 0.0, 1.0);
	g = UsefulFunct::Clamp(g, 0.0, 1.0);
	b = UsefulFunct::Clamp(b, 0.0, 1.0);

	y = img_height - y - 1;
	int index = (x + (y * img_width)) * num_channel;

	pixels[index]	  = static_cast<uint8_t>(255.0 * r);
	pixels[index + 1] = static_cast<uint8_t>(255.0 * g);
	pixels[index + 2] = static_cast<uint8_t>(255.0 * b);
}

// STB wrapper
void ImageHandler::WriteToPNG(const std::string& filename)
{
	stbi_write_png(filename.c_str(), 
				   img_width,
				   img_height,
				   num_channel,
				   pixels.get(), 
				   img_width * num_channel);
}