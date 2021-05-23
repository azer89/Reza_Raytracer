
#ifndef __IMAGE_WRAPPER_H__
#define __IMAGE_WRAPPER_H__

#include <string>
//#include <vector>
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
	// constructor
	ImageHandler(int img_width, int img_height);
	
	// destructor
	~ImageHandler();

	// using STB
	void WriteToPNG(const std::string& filename);

	// old
	void SetPixel(double r, double g, double b);	
	
	// new
	void SetPixel(double r, double g, double b, int x, int y);
	
};

#endif
