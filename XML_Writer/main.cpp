// XML_Writer.cpp : définit le point d'entrée pour l'application console.
//


#include "stdafx.h"
#include "Obstacle.h"
#include "XMLWriter.h"
#include "XMLReader.h"
#include <iostream>
using namespace std;
int _tmain(int argc, _TCHAR* argv[])
{
	XMLWriter xmlw("level.xml", "Level test", 100, 120);
	XMLReader xmlr("level2.xml");
	Obstacle obstacle(2, 1, Obstacle::CAISSE);
	xmlw.writeObstacle(obstacle);
	vector<Obstacle>* obsLu= NULL;
	obsLu = xmlr.read();
	for (int i = 0; i < obsLu->size(); i++)
		cout << "position : " << obsLu->at(i).getPosition() << " ; hauteur : " << obsLu->at(i).getHauteur() << " ; type : " << obsLu->at(i).getType() << endl;
	system("pause");
	return 0;
}

