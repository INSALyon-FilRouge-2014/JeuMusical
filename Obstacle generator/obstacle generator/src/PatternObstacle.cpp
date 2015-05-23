#include <iostream>
#include <vector>
#include <cstdlib>
#include "Obstacle.h"
#include "PatternObstacle.h"


//pas terminé
void PatternObstacle::addObstacle(Obstacle o, int index)
{

}

vector<Obstacle> PatternObstacle::getObstacles()
{
	return obstacles;
}


int PatternObstacle::getDenivelee()
{
	return h_min - h_max;
}

int PatternObstacle::getUpDistance()
{
    //différence entre le premier obstacle et l'obstacle le plus proche du plafond
    return abs(obstacles[0].getHauteur() - h_min);
}

int PatternObstacle::getDownDistance()
{
     //différence entre le premier obstacle et l'obstacle le plus proche du sol
    return abs(h_max - obstacles[0].getHauteur());
}


int PatternObstacle::getLength()
{
	return obstacles.size();
}

//donne une hauteur de départ et mets a jour tous les obstacles suivants par rapport à cette hauteur de départ
void PatternObstacle::setStartHeight(int height)
{
	for (std::vector<Obstacle>::iterator it = obstacles.begin(); it != obstacles.end(); ++it)
	{
		it->setHauteur(it->getHauteur() - obstacles[0].getHauteur() + height);
	}
}

int PatternObstacle::getEndHeight()
{
	return obstacles[obstacles.size()-1].getHauteur();
}

PatternObstacle::PatternObstacle()
{
	h_min = Obstacle::H_PLAFOND;
	h_max = Obstacle::H_SOL;
}

PatternObstacle::PatternObstacle(vector<Obstacle> vo)
{
	obstacles = vo;
	h_min = Obstacle::H_PLAFOND;
	h_max = Obstacle::H_SOL;

	for (std::vector<Obstacle>::iterator it = obstacles.begin(); it != obstacles.end(); ++it)
	{
		int h = it->getHauteur();
		if(h > h_max)
		{
			h_max = h;
		}
		if(h < h_min)
		{
			h_min = h;
		}
	}
}


PatternObstacle::~PatternObstacle()
{

}
