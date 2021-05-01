
#ifndef __STB_WRAPPER__
#define __STB_WRAPPER__

#include <string>
#include <vector>
#include <memory>

// this class handles the output image
class ImageHandler
{
private:
	// need to be able to reset pixel_iterator
	int pixel_iterator;
	std::unique_ptr<uint8_t[]> pixels;

	int img_width;
	int img_height;
	int num_channel;
	
public:
	ImageHandler(int img_width, int img_height);

	void SetPixel(uint8_t r, uint8_t g, uint8_t b);
	
	void WriteToPNG(const std::string& filename/*, uint8_t* pixels, int width, int height*/);
};

#endif
