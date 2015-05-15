#include "stdafx.h"
#include "XMLReader.h"

#include <iostream>

using namespace std;

XMLReader::XMLReader(char* chemin)
{
	TiXmlDocument doc2(chemin);
	doc = doc2;
}

vector<Platform>* XMLReader::read()
{
	vector<Platform>* Platforms = new vector<Platform>;
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
			
			Platform::TypeObstacle type = (Platform::TypeObstacle) atoi(elem->Attribute("type"));
			cout << "type : " << type << endl;

			// On le rajoute a la liste
			Platform ob(pos, hauteur, type);
			Platforms->push_back(ob);
		}
		return Platforms;
	}
	else
	{
		cout << "Could not load XML File.";
	}
}

XMLReader::~XMLReader()
{
}
