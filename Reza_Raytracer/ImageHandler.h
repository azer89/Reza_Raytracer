#ifndef __IMAGE_WRAPPER_H__
#define __IMAGE_WRAPPER_H__

#include <string>
#include <memory>

// A wrapper for STB library that handles the output image
class ImageHandler
{
private:
	std::unique_ptr<uint8_t[]> pixels;

	int img_width;
	int img_height;
	int num_channel;

public:
	// Constructor
	ImageHandler(int img_width, int img_height);

	// Destructor
	~ImageHandler();

	// using STB
	void WriteToPNG(const std::string& filename);

	void SetPixel(double r, double g, double b, int x, int y);
};

#endif
