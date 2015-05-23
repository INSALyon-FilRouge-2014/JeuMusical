#include <vector>
#include <cstdlib>
#include <time.h>
#include "PatternObstacleManager.h"
#include "PatternObstacle.h"

using namespace std;


void PatternObstacleManager::addPatternObstacle(PatternObstacle pat)
{
    patterns.push_back(pat);
}

PatternObstacle PatternObstacleManager::getRandomPattern(int length, int max_height, int start_height)
{
    vector<PatternObstacle> selected;
    int minimum_height_allowed = Obstacle::H_PERSO + Obstacle::H_PLAFOND;
    int maximum_height_allowed = Obstacle::H_SOL;

    for (std::vector<PatternObstacle>::iterator it = patterns.begin(); it != patterns.end(); ++it)
    {
    	if(it->getLength() == length)
    	{
    	    //plafond vers les petites valeurs, sol vers les grandes
    	    if(( (start_height - it->getUpDistance()) < minimum_height_allowed) && ( (start_height + it->getDownDistance()) > maximum_height_allowed))
            {
                //on peut prendre ce pattern
                selected.push_back(*it);
            }
    	}
    }

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

