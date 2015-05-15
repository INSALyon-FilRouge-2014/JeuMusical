#include "XMLWriter.h"

using namespace std;



XMLWriter::XMLWriter(string filename, string nom, int longueur, int bpm, float vitesse)
{
	os.open(filename);
	os << "<niveau nom=\"" << nom << "\" longueur=\"" << longueur << "\" bpm=\"" << bpm << "\" vitesse=\"" << vitesse << "\"/>" << endl;
}

bool XMLWriter::writeObstacle(Obstacle obs)
{
	os << "<bloc position=\"" << obs.getPosition() << "\" hauteur=\"" << obs.getHauteur() << "\" type=\"" << obs.getType() << "\" positionPCM=\"" << obs.getPCMPosition() << "\" positionPCM1024=\"" << obs.getPCM1024Position() << "\" positionMS=\"" << obs.getMSPosition() << "\" />" << endl;
	return true;
}

XMLWriter::~XMLWriter()
{
	os.close();
}
