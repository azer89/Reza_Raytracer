#ifndef __OBJ_READER_H__
#define __OBJ_READER_H__


#include "Vec3.h"
#include <vector>
#include <string>

class FileReader
{
	

public:

	FileReader()
	{
	}

	void ReadOBJ(const std::string& filename,
				 std::vector<Vec3>& vertices,
				 std::vector< std::vector<int>>& faces);
};

#endif