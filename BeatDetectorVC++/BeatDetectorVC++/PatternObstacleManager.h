#ifndef PATTERNOBSTACLEMANAGER_H
#define PATTERNOBSTACLEMANAGER_H

#include <iostream>
#include <vector>
#include "PatternObstacle.h"

class PatternObstacleManager
{
public:
    void addPatternObstacle(PatternObstacle pat);

	PatternObstacle getRandomPattern(int length, int start_height);

	void loadPatterns();

	int countLoadedPattern();

	PatternObstacleManager(int seed);

	PatternObstacleManager(int seed, std::vector<PatternObstacle> p);

    virtual ~PatternObstacleManager();

private:
	std::vector<PatternObstacle> patterns;
};

#endif