#include <vector>
#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <time.h>
#include "PatternObstacleManager.h"
#include "PatternObstacle.h"

using namespace std;


void PatternObstacleManager::addPatternObstacle(PatternObstacle pat)
{
    patterns.push_back(pat);
}

void PatternObstacleManager::loadPatterns()
{
    /**
    * Legende  :
    * C caisse
    * N nuage
    **/

    PatternObstacle p1, p2, p3, p4, p5, p6, p7, p8, p9;

    Obstacle ob_8C(8,Obstacle::CAISSE);
    Obstacle ob_7C(7,Obstacle::CAISSE);
    Obstacle ob_6C(6,Obstacle::CAISSE);
    Obstacle ob_5C(5,Obstacle::CAISSE);
    Obstacle ob_4C(4,Obstacle::CAISSE);
    Obstacle ob_3C(3,Obstacle::CAISSE);

    Obstacle ob_8N(8,Obstacle::NUAGE);
    Obstacle ob_7N(7,Obstacle::NUAGE);
    Obstacle ob_6N(6,Obstacle::NUAGE);
    Obstacle ob_5N(5,Obstacle::NUAGE);
    Obstacle ob_4N(4,Obstacle::NUAGE);
    Obstacle ob_3N(3,Obstacle::NUAGE);

    //la position absolue n'ets pas importante ici
    //c'est la position relative des blocks entre eux qui compte
    //ils seront amenés à être repositionnés en hauteur tous ensemble

    /** Pattern 1
    *1
    *2
    *3
    *4  C   C   C   C
    **/
    p1.addObstacle(0,ob_3C);
    p1.addObstacle(1,ob_3C);
    p1.addObstacle(2,ob_3C);
    p1.addObstacle(3,ob_3C);

    /** Pattern 2
    *1
    *2
    *3
    *4  N   N   N   N
    **/
    p2.addObstacle(0,ob_3N);
    p2.addObstacle(1,ob_3N);
    p2.addObstacle(2,ob_3N);
    p2.addObstacle(3,ob_3N);

    /** Pattern 3
    *1
    *2
    *3  N   N
    *4          N   N
    **/
    p3.addObstacle(0,ob_3N);
    p3.addObstacle(1,ob_3N);
    p3.addObstacle(2,ob_4N);
    p3.addObstacle(3,ob_4N);

    /** Pattern 4
    *1
    *2
    *3          N   N
    *4  N   N
    **/
    p4.addObstacle(0,ob_4N);
    p4.addObstacle(1,ob_4N);
    p4.addObstacle(2,ob_3N);
    p4.addObstacle(3,ob_3N);

    addPatternObstacle(p1);
    //addPatternObstacle(p2);
    addPatternObstacle(p3);
    addPatternObstacle(p4);
}

PatternObstacle PatternObstacleManager::getRandomPattern(int length, int start_height)
{
    vector<PatternObstacle> selected;
    int minimum_height_allowed = Obstacle::H_PERSO + Obstacle::H_PLAFOND;
    int maximum_height_allowed = Obstacle::H_SOL;

    for (std::vector<PatternObstacle>::iterator it = patterns.begin(); it != patterns.end(); ++it)
    {
        //cout << "Test pour ";
        //it->display();
    	if(it->getLength() == length)
    	{
    	    //cout << "meme length !" << endl;
    	    //printf("(start_height - it->getUpDistance()) > minimum_height_allowed\n");
    	    //printf("%d - %d > %d\n",start_height,it->getUpDistance(),minimum_height_allowed);
    	    //printf("(start_height + it->getDownDistance()) < maximum_height_allowed\n");
    	    //printf("%d + %d < %d\n",start_height,it->getDownDistance(),maximum_height_allowed);
    	    //plafond vers les petites valeurs, sol vers les grandes
    	    if(( (start_height - it->getUpDistance()) > minimum_height_allowed) && ( (start_height + it->getDownDistance()) < maximum_height_allowed))
            {
                //cout << "bonne disposition ! " << endl;
                //on peut prendre ce pattern
                selected.push_back(*it);
                //cout << "obstacle selectionnée : ";
                //it->display();
            }
    	}
    }
    cout << selected.size() <<" patterns selectionnes " << endl;
    //des obstacles ont été pré-selectionnés
    int index = rand() % selected.size();

    //on adapte les obstacles a la start_height
    selected[index].setStartHeight(start_height);
    return selected[index];
}

PatternObstacleManager::PatternObstacleManager(int seed)
{
    srand(seed);
}

PatternObstacleManager::PatternObstacleManager(int seed, vector<PatternObstacle> p)
{
    srand(seed);
    patterns = p;
}

PatternObstacleManager::~PatternObstacleManager()
{
    srand(time(NULL));
}

