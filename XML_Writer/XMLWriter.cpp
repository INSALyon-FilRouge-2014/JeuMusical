
#include "stdafx.h"
#include "XMLWriter.h"
#include "tinyxml.h"

using namespace std;



XMLWriter::XMLWriter(string filename, string nom, int longueur, int bpm)
{
	os.open(filename);
	os << "<niveau nom=\"" << nom << "\" longueur=\"" << longueur << "\" vitesse=\"" << bpm << "\"/>" << endl;
}

bool XMLWriter::writeObstacle(Obstacle obs)
{
	os << "<bloc position=\"" << obs.getPosition() << "\" hauteur=\"" << obs.getHauteur() << "\" type=\"" << obs.getType() << "\"/>" << endl;
	return true;
}
/*
Obstacle XMLWriter::read()
{
	TiXmlDocument doc("level.xml");
	TiXmlHandle hdl(&doc);
	TiXmlElement *elem = hdl.FirstChildElement("bloc").Element();
	int pos = atoi(elem->Attribute("position"));
	int hauteur = atoi(elem->Attribute("hauteur"));
	Obstacle::TypeObstacle type = (Obstacle::TypeObstacle) atoi(elem->Attribute("type"));
	Obstacle* obstacles = new Obstacle(pos, hauteur, type);
	return *obstacles;
}*/


XMLWriter::~XMLWriter()
{
	os.close();
}
