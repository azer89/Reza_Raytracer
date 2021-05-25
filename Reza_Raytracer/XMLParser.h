#ifndef __XMLPARAMETERS_H__
#define __XMLPARAMETERS_H__


#include "Vec3.h"


// A class that contains parameters taken from main.xml
// Also a wrapper to tinyxml2
class XMLParser
{
public:
	XMLParser();
	~XMLParser();

	static void LoadParametersFromXML();


};

#endif
