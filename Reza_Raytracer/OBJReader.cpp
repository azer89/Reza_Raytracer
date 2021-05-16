
#include "OBJReader.h"


#include <fstream>
#include <sstream>

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


inline bool StartWith(const std::string& prefix, 
					  const std::string& argument)
{
	if (argument.substr(0, prefix.size()) == prefix)
	{
		return true;
	}
	return false;
}

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

			faces.push_back({i1 - 1, 
							 i2 - 1, 
							 i3 - 1});
		}
	}

	
	f.close();
}