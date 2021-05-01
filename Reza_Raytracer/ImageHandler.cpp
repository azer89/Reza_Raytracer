
#include "ImageHandler.h"


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
	//delete[] pixels;
}

void ImageHandler::SetPixel(double r, double g, double b)
{
	pixels[pixel_iterator++] = static_cast<uint8_t>(255.0 * r);
	pixels[pixel_iterator++] = static_cast<uint8_t>(255.0 * g);
	pixels[pixel_iterator++] = static_cast<uint8_t>(255.0 * b);
}


void ImageHandler::WriteToPNG(const std::string& filename/*,
	                        uint8_t* pixels, 
	                        int width, 
	                        int height*/)
{
	// chanhaeng.blogspot.com/2018/12/how-to-use-stbimagewrite.html
	
	stbi_write_png(filename.c_str(), 
		img_width,
		img_height,
		num_channel,
		pixels.get(), 
		img_width * num_channel);
}



