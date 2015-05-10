#ifndef XMLREADER_H_
#define XMLREADER_H_

#include <fstream>
#include <string>
#include <list>
#include <vector>
#include "Platform.h"
#include "tinyxml.h"

class XMLReader
{
public:
	XMLReader(char* str);
	~XMLReader();
	//Lis toutes les balises de type "bloc" et place les objets ainsi créés dans un tableau
	std::vector<Platform>* read();
protected:
	TiXmlDocument doc;
};

#endif

