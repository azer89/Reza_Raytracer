#include "OBJReader.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <string>

inline std::vector<std::string> Split(const std::string& s,  char delim)
{
	std::vector<std::string> elems;

	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delim))
	{
		elems.push_back(item);
	}

	return elems;
}

// Elements can be empty strings if the input is invalid
inline std::vector<std::string> Split(const std::string& s, const std::string& delim)
{
	std::vector<std::string> elements;

	auto start = 0;
	auto end = s.find(delim);
	while (end != s.npos)
	{
		elements.push_back(s.substr(start, end - start));
		start = end + delim.size();
		end = s.find(delim, start);
	}

	elements.push_back(s.substr(start, end - start));

	return elements;
}

inline bool StartWith(const std::string& prefix, 
					  const std::string& argument)
{
	if (argument.substr(0, prefix.size()) == prefix)
	{
		return true;
	}
	return false;
}

// Only supports "v" and "f" 
void OBJReader::ReadOBJ(const std::string& filename,
						std::vector<Vec3>& vertices,
						std::vector< std::vector<int>>& faces)
{
	std::ifstream f(filename);
	while (!f.eof())
	{
		std::string line;
		std::getline(f, line);

		if (line.size() == 0) 
		{ 
			continue; 
		}

		std::vector<std::string> str_array = Split(line, ' ');

		if (StartWith("v", line) && str_array.size() == 4)
		{
			vertices.push_back(Vec3(std::stod(str_array[1]),
									std::stod(str_array[2]),
									std::stod(str_array[3]) ));
		}
		else if (StartWith("f", line) && str_array.size() == 4)
		{
			int i1 = std::stoi( Split(str_array[1], '/')[0] );
			int i2 = std::stoi( Split(str_array[2], '/')[0] );
			int i3 = std::stoi( Split(str_array[3], '/')[0] );

			// OBJ indexing starts with 1
			faces.push_back({i1 - 1, 
							 i2 - 1, 
							 i3 - 1});
		}
	}
	
	f.close();
}

// TODO: Need to support "vt"
void OBJReader::ReadOBJ(const std::string& filename,
						std::vector<Vec3>& vertices,				   // vertex list
						std::vector<Vec3>& normals,					   // normal vector list
						std::vector<Vec2>& uvs,						   // texture uvs
						std::vector<std::vector<int>>& vertex_indices, // triangle faces
						std::vector<std::vector<int>>& normal_indices, // normal vector indices for triangles
						std::vector<std::vector<int>>& uv_indices)	   // uv indices for triangles
{
	// Can be "//" or "/"
	std::string delim = "//";

	std::ifstream f(filename);
	while (!f.eof())
	{
		std::string line;
		std::getline(f, line);

		if (line.size() == 0)
		{
			continue;
		}

		std::vector<std::string> str_array = Split(line, ' ');

		// Texture coordinates
		if (StartWith("vt", line) && str_array.size() == 3)
		{
			delim = "/";

			uvs.push_back(Vec2(std::stod(str_array[1]), std::stod(str_array[2])));

		}
		// Vertex normals
		if (StartWith("vn", line) && str_array.size() == 4)
		{
			normals.push_back(Vec3(std::stod(str_array[1]),
								   std::stod(str_array[2]),
								   std::stod(str_array[3]) ));
		}
		// Vertex positions
		else if (StartWith("v", line) && str_array.size() == 4)
		{
			vertices.push_back(Vec3(std::stod(str_array[1]),
									std::stod(str_array[2]),
									std::stod(str_array[3]) ));
		}
		// Triangles
		else if (StartWith("f", line) && str_array.size() == 4)
		{
			auto s1 = Split(str_array[1], delim);
			auto s2 = Split(str_array[2], delim);
			auto s3 = Split(str_array[3], delim);

			int i1 = std::stoi(s1[0]);
			int i2 = std::stoi(s2[0]);
			int i3 = std::stoi(s3[0]);
			
			// OBJ indexing starts with 1
			vertex_indices.push_back({ i1 - 1,
									   i2 - 1,
									   i3 - 1 });

			// TODO: code a little bit ugly
			if (uvs.size() > 0)
			{
				int uv1 = std::stoi(s1[1]);
				int uv2 = std::stoi(s2[1]);
				int uv3 = std::stoi(s3[1]);

				uv_indices.push_back({ uv1 - 1,
									   uv2 - 1,
									   uv3 - 1 });

				int n1 = std::stoi(s1[2]);
				int n2 = std::stoi(s2[2]);
				int n3 = std::stoi(s3[2]);

				normal_indices.push_back({ n1 - 1,
										   n2 - 1,
										   n3 - 1 });
			}
			else
			{
				int n1 = std::stoi(s1[1]);
				int n2 = std::stoi(s2[1]);
				int n3 = std::stoi(s3[1]);

				normal_indices.push_back({ n1 - 1,
										   n2 - 1,
										   n3 - 1 });
			}
		}
	}

	f.close();
}