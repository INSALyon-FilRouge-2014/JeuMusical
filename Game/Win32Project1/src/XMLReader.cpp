#include "stdafx.h"
#include "XMLReader.h"


using namespace std;

XMLReader::XMLReader(char* chemin)
{
	TiXmlDocument doc2(chemin);
	doc = doc2;
}

vector<Obstacle>* XMLReader::read()
{
	vector<Obstacle>* obstacles = new vector<Obstacle>;
	if (doc.LoadFile())
	{
		TiXmlHandle hdl(&doc);
		for (TiXmlElement* elem = hdl.FirstChildElement("bloc").Element(); elem; elem = elem->NextSiblingElement("bloc"))
		{
			TiXmlHandle hdl(&doc);
			/********************************************/
			/*         LECTURE D'UN ATTRIBUT            */
			/********************************************/
			// elem est la balise courante sur laquelle on travaille
			// elem->Attribute("monAttribut") récupère la valeur de l'attribut monAttribut
			// La valeur d'un attribut est à convertir !
			int pos = atoi(elem->Attribute("position"));
			cout << "pos : " << pos << endl;

			int hauteur = atoi(elem->Attribute("hauteur"));
			cout << "hauteur : " << hauteur << endl;

			Obstacle::TypeObstacle type = (Obstacle::TypeObstacle) atoi(elem->Attribute("type"));
			cout << "type : " << type << endl;

			// On le rajoute a la liste
			Obstacle ob(pos, hauteur, type);
			obstacles->push_back(ob);
		}
		return obstacles;
	}
	else
	{
		cout << "Could not load XML File.";
	}
}

XMLReader::~XMLReader()
{
}
