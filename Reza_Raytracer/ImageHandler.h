#ifndef __IMAGE_WRAPPER_H__
#define __IMAGE_WRAPPER_H__

#include <string>
#include <memory>

// this class handles the output image
// which also a wrapper for STB library
class ImageHandler
{
private:
	std::unique_ptr<uint8_t[]> pixels;
	
	int img_width;
	int img_height;
	int num_channel;
	
public:
	// constructor
	ImageHandler(int img_width, int img_height);
	
	// destructor
	~ImageHandler();

	// using STB
	void WriteToPNG(const std::string& filename);

	// new
	void SetPixel(double r, double g, double b, int x, int y);
};

#endif
