
#include "OBJReader.h"

#include <fstream>
#include <sstream>
#include <iostream>

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

// elements can be empty strings if the input is invalid
inline std::vector<std::string> Split(const std::string& s, const std::string& delim)
{
	std::vector<std::string> s_array;

	auto start = 0;
	auto end = s.find(delim);
	while (end != s.npos)
	{
		s_array.push_back(s.substr(start, end - start));
		start = end + delim.size();
		end = s.find(delim, start);
	}

	s_array.push_back(s.substr(start, end - start));

	return s_array;
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

// Supports "v" and "f" 
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

// Supports "v", "vn", and "f" 
void OBJReader::ReadOBJ(const std::string& filename,
						std::vector<Vec3>& vertices, // vertex list
						std::vector<Vec3>& normals,  // normal vector list
						std::vector< std::vector<int>>& vertex_indices, // triangle faces
						std::vector< std::vector<int>>& normal_indices) // normal vector indices for triangles
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

		if (StartWith("vn", line) && str_array.size() == 4)
		{
			normals.push_back(Vec3(std::stod(str_array[1]),
								   std::stod(str_array[2]),
								   std::stod(str_array[3]) ));
		}
		else if (StartWith("v", line) && str_array.size() == 4)
		{
			vertices.push_back(Vec3(std::stod(str_array[1]),
									std::stod(str_array[2]),
									std::stod(str_array[3]) ));
		}
		else if (StartWith("f", line) && str_array.size() == 4)
		{
			auto s1 = Split(str_array[1], "//");
			auto s2 = Split(str_array[2], "//");
			auto s3 = Split(str_array[3], "//");

			int i1 = std::stoi(s1[0]);
			int i2 = std::stoi(s2[0]);
			int i3 = std::stoi(s3[0]);

			

			// OBJ indexing starts with 1
			vertex_indices.push_back({ i1 - 1,
									   i2 - 1,
									   i3 - 1 });

			// TODO code a little bit ugly
			// cannot find normal vectors
			if(normals.size() > 0)
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