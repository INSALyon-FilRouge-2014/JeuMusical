// XML_Writer.cpp : définit le point d'entrée pour l'application console.
//


#include "stdafx.h"
#include "Obstacle.h"
#include "XMLWriter.h"
#include <iostream>
using namespace std;
int _tmain(int argc, _TCHAR* argv[])
{
	XMLWriter xmlw("level.xml", "Level test", 100, 120);
	Obstacle obstacle(2, 1, Obstacle::CAISSE);
	xmlw.writeObstacle(obstacle);
	//Obstacle obsLu = xmlw.read();
	//cout << "position :" << obsLu.getPosition() << " ; hauteur : " << obsLu.getHauteur() << " ; type : " << obsLu.getType() << endl;
	return 0;
}

