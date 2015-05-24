#ifndef XMLREADER_H_
#define XMLREADER_H_

#include <fstream>
#include <string>
#include <list>
#include <vector>
#include "Platform.h"
#include "tinyxml.h"

struct LevelInfo
{
	std::string nom;
	int longueur;
	int bpm;
	double vitesse;

};


class XMLReader
{
public:
	XMLReader(std::string str);
	~XMLReader();
	//Lis toutes les balises de type "bloc" et place les objets ainsi créés dans un tableau
	std::vector<Platform>* readPlatform();
	LevelInfo readInfo();
protected:
	TiXmlDocument doc;
};

#endif

