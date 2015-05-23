#ifndef PATTERNOBSTACLE_H
#define PATTERNOBSTACLE_H

#include <iostream>
#include <vector>
#include <map>
#include "Obstacle.h"

using namespace std;

typedef map<int,vector<Obstacle>> Pattern;

class PatternObstacle
{

public:
	void addObstacle(int index, Obstacle o);

	Pattern getObstacles();

   	Pattern getFilledObstacles();

	int getDenivelee();//retourne la denivelée, positive (donc descendante comme plafond = 1)

    //distance entre le premier obstacle et l'obstacle le plus haut
	int getUpDistance();

    //distance entre le premier obstacle et l'obstacle le plus bas
	int getDownDistance();

	int getLength();

	void setStartHeight(int height);

	int getEndHeight();

    void display();

	PatternObstacle();

	PatternObstacle(Pattern pat);

	virtual ~PatternObstacle();


private:
	Pattern obstacles;

	int h_max; //hauteur max parmis les obstacles

	int h_min; //hauteur min parmis les obstacles
};

#endif
