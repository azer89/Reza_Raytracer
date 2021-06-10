#ifndef __XMLPARAMETERS_H__
#define __XMLPARAMETERS_H__


#include "Vec3.h"

#include <unordered_map>
#include <vector>

class Material;
class Hittable;

// A class that contains parameters taken from main.xml
// Also a wrapper to tinyxml2
class XMLParser
{
public:
	//XMLParser();
	//~XMLParser();

	void LoadParametersFromXML();

	void LoadMaterialsAndObjects(std::unordered_map<std::string, shared_ptr<Material>>& mat_map,
								 std::vector<shared_ptr<Hittable>>& objects);

};

#endif