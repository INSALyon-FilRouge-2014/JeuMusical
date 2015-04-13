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

XMLWriter::~XMLWriter()
{
	os.close();
}
