#ifndef PATTERNOBSTACLE_H
#define PATTERNOBSTACLE_H

#include <iostream>
#include <vector>
#include "Obstacle.h"

using namespace std;

class PatternObstacle
{

public:
	void addObstacle(Obstacle o, int index);

	vector<Obstacle> getObstacles();

	int getDenivelee();//retourne la denivelée, positive (donc descendante comme plafond = 1)

    //distance entre le premier obstacle et l'obstacle le plus haut
	int getUpDistance();

    //distance entre le premier obstacle et l'obstacle le plus bas
	int getDownDistance();

	int getLength();

	void setStartHeight(int height);

	int getEndHeight();

	PatternObstacle();

	PatternObstacle(vector<Obstacle> vo);

	virtual ~PatternObstacle();


private:
	vector<Obstacle> obstacles;

	int h_max; //hauteur max parmis les obstacles

	int h_min; //hauteur min parmis les obstacles
};

#endif
