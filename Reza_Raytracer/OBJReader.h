#ifndef __OBJ_READER_H__
#define __OBJ_READER_H__

#include "Vec2.h"
#include "Vec3.h"
#include <vector>
#include <string>

class OBJReader
{
public:
	OBJReader()
	{
	}

	// Supports "v" and "f" 
	void ReadOBJ(const std::string& filename,
				 std::vector<Vec3>& vertices,
				 std::vector< std::vector<int>>& faces);

	// Supports "v", "vn", "vt", and "f"
	void ReadOBJ(const std::string& filename,
				 std::vector<Vec3>& vertices,
				 std::vector<Vec3>& normals,
				 std::vector<Vec2>& uvs,
				 std::vector<std::vector<int>>& vertex_indices,
				 std::vector<std::vector<int>>& normal_indices,
				 std::vector<std::vector<int>>& uv_indices);
};

#endif