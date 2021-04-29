
#ifndef __STB_WRAPPER__
#define __STB_WRAPPER__

#include <string>
#include <vector>

class STBWrapper
{
public:
	static void WriteToPNG(const std::string& filename, uint8_t* data, int width, int height);
};

#endif
