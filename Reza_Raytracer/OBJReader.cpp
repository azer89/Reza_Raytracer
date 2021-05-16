
#include "OBJReader.h"


#include <fstream>
#include <sstream>

std::vector<std::string> Split(const std::string& s,  char delim)
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


inline bool StartWith(const std::string& prefix, const std::string& argument)
{
	if (argument.substr(0, prefix.size()) == prefix)
	{
		return true;
	}
	return false;
}

// github.com/azer89/MangaVectorizer/blob/master/CVSystem/OBJIO.cpp
void OBJReader::ReadOBJ(const std::string& filename, 
						std::vector<Vec3>& vertices,
						std::vector< std::vector<int>>& faces)
{
	std::ifstream f(filename);
	while (!f.eof())
	{
		std::string line;
		std::getline(f, line);

		if (line.size() == 0) { continue; }
		std::vector<std::string> arrayStr = Split(line, ' ');

		if (StartWith("v", line) && arrayStr.size() == 4)
		{
			vertices.push_back(Vec3(std::stod(arrayStr[1]), 
									std::stod(arrayStr[2]), 
									std::stod(arrayStr[3]) ));
		}

		if (StartWith("f", line) && arrayStr.size() == 4)
		{
			int i1 = std::stoi( Split(arrayStr[1], '/')[0] );
			int i2 = std::stoi( Split(arrayStr[2], '/')[0] );
			int i3 = std::stoi( Split(arrayStr[3], '/')[0] );

			faces.push_back({i1, i2, i3});

			/*faces.push_back({ std::stoi(arrayStr[1]),
							    std::stoi(arrayStr[2]),
							    std::stoi(arrayStr[3]) });*/
		}
	}

	
	f.close();
}