#include <iostream>
#include <vector>
#include <map>
#include <cstdio>
#include <cstdlib>
#include "Obstacle.h"
#include "PatternObstacle.h"


void PatternObstacle::addObstacle(int index, Obstacle o)
{
    //printf("Insertion d'un Obstacle dans le pattern ...\n");
    //printf("\tAvant : h_min = %d / h_max = %d\n",h_min,h_max);
    //on met à jour le min et max
    int h = o.getHauteur();
    //printf("Hauteur de l'obstacle : %d\n",h);

    if(obstacles.size() == 0)
    {
        h_min = h;
        h_max = h;
    }
    else
    {
        if(h > h_max)
        {
            h_max = h;
        }
        if(h < h_min)
        {
            h_min = h;
        }
    }
    //printf("\tApres : h_min = %d / h_max = %d\n",h_min,h_max);

    Pattern::iterator it_insert = obstacles.find(index);
    if(it_insert != obstacles.end())
    {
        //trouvé
        it_insert->second.push_back(o);
    }
    else
    {
        //pas trouvé
        vector<Obstacle> v;
        v.push_back(o);
        obstacles.insert(make_pair(index, v));
    }


}

Pattern PatternObstacle::getObstacles()
{
	return obstacles;
}

//rempli jusqu'au sol de caiss si l'obstacle est une caisse
Pattern PatternObstacle::getFilledObstacles()
{
    /**TODO**/
    return obstacles;
}

int PatternObstacle::getDenivelee()
{
	return h_min - h_max;
}

//précond : au moins un obstacle
int PatternObstacle::getUpDistance()
{
    //différence entre le premier obstacle et l'obstacle le plus proche du plafond
    //premier vector de la map (obstacles[0]) premiere valeur de ce vecteur (obstacles[0][0]
    return abs(obstacles[0][0].getHauteur() - h_min);
}

//précond : au moins un obstacle
int PatternObstacle::getDownDistance()
{
     //différence entre le premier obstacle et l'obstacle le plus proche du sol
    return abs(h_max - obstacles[0][0].getHauteur());
}


int PatternObstacle::getLength()
{
	return obstacles.size();
}

//donne une hauteur de départ et mets a jour tous les obstacles suivants par rapport à cette hauteur de départ
//précond : au moins un obstacle
void PatternObstacle::setStartHeight(int height)
{
    int h_first = obstacles[0][0].getHauteur();
	for(Pattern::iterator it_map = obstacles.begin(); it_map != obstacles.end(); it_map++)
    {
        for (std::vector<Obstacle>::iterator it_vec = it_map->second.begin(); it_vec != it_map->second.end(); ++it_vec)
        {
            it_vec->setHauteur(it_vec->getHauteur() - h_first + height);
        }
    }
    h_max = h_max - h_first + height;
    h_min = h_min - h_first + height;
}

int PatternObstacle::getEndHeight()
{
    vector<Obstacle> last_vec = obstacles[obstacles.size() - 1];
	int min = Obstacle::H_SOL;
	for (std::vector<Obstacle>::iterator it = last_vec.begin(); it != last_vec.end(); ++it)
	{
		if(it->getHauteur() < min)
		{
			min = it->getHauteur();
		}
	}
	return min;
}

void PatternObstacle::display()
{
    printf("PatternObstacle : h_min = %d / h_max = %d\n",h_min, h_max);
    for (Pattern::iterator it_map = obstacles.begin(); it_map != obstacles.end(); ++it_map)
	{
		for (std::vector<Obstacle>::iterator it_vec = it_map->second.begin(); it_vec != it_map->second.end(); ++it_vec)
		{
            printf("\t%d-",it_map->first);
            it_vec->display();
            printf("\n");
		}
	}
}

PatternObstacle::PatternObstacle()
{
	h_min = 0;
	h_max = 0;
}

PatternObstacle::PatternObstacle(Pattern pat)
{
	obstacles = pat;
	h_min = 0;
	h_max = 0;

    if(obstacles.size() != 0 && obstacles[0].size() != 0)
    {
        //il y a un premier element
        h_min = obstacles[0][0].getHauteur();
        h_max = obstacles[0][0].getHauteur();
    }

	for (Pattern::iterator it_map = obstacles.begin(); it_map != obstacles.end(); ++it_map)
	{
		for (std::vector<Obstacle>::iterator it_vec = it_map->second.begin(); it_vec != it_map->second.end(); ++it_vec)
		{
			int h = it_vec->getHauteur();
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
}


PatternObstacle::~PatternObstacle()
{

}
