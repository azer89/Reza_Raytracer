
#include "STBWrapper.h"

// chanhaeng.blogspot.com/2018/12/how-to-use-stbimagewrite.html

//#include <fstream>
//#include <sstream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STBI_MSC_SECURE_CRT
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

void STBWrapper::WriteToPNG(const std::string& filename, 
	                        uint8_t* pixels, 
	                        int width, 
	                        int height)
{
	// if channel_num is 4, you can use alpha channel in png
	int channel_num = 3;
	stbi_write_png(filename.c_str(), 
				   width, 
				   height, 
				   channel_num, 
				   pixels, 
				   width * channel_num);
}



