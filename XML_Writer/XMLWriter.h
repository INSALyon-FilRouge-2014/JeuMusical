#ifndef XMLWRITER_H_
#define XMLWRITER_H_

#include <fstream>
#include <string>
#include <list>
#include "Obstacle.h"

class XMLWriter
{
public:
	bool writeObstacle(Obstacle o);
	//Obstacle read();
	//constructeur
	XMLWriter(std::string filename, std::string nom, int longueur, int bpm);
	//destructeur
	virtual ~XMLWriter();
protected:
	std::ofstream os;
};

#endif

