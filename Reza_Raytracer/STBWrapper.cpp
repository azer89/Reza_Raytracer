
#include "STBWrapper.h"

// chanhaeng.blogspot.com/2018/12/how-to-use-stbimagewrite.html

//#define STB_IMAGE_IMPLEMENTATION
//#include "stb_image.h"
//
//#define STBI_MSC_SECURE_CRT
//#define STB_IMAGE_WRITE_IMPLEMENTATION
//#include "stb_image_write.h"

void STBWrapper::WriteToPNG(const std::string& filename, 
	                        uint8_t* data, 
	                        int width, 
	                        int height)
{
	/*const int n_channel = 3;
	
	stbi_write_png(filename.c_str(),
		           width, 
		           height, 
		           n_channel,
		           &data, 
		width * n_channel);*/
}



