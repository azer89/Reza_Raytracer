#ifndef __OBJ_READER_H__
#define __OBJ_READER_H__


#include "Vec3.h"
#include <vector>
#include <string>

class OBJReader
{
public:
	OBJReader()
	{

	}

	void ReadOBJ(const std::string& filename,
				 std::vector<Vec3>& vertices,
				 std::vector< std::vector<int>>& faces);

	void ReadOBJ(const std::string& filename,
				 std::vector<Vec3>& vertices,
				 std::vector<Vec3>& normals,
				 std::vector< std::vector<int>>& vertex_indices,
				 std::vector< std::vector<int>>& normal_indices);
};

#endif