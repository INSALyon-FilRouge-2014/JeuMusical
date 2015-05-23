#include <iostream>
#include <vector>
#include "PatternObstacle.h"

class PatternObstacleManager
{
public:
    void addPatternObstacle(PatternObstacle pat);

	PatternObstacle getRandomPattern(int length, int max_height, int start_height);

	PatternObstacleManager(int seed);

	PatternObstacleManager(int seed, std::vector<PatternObstacle> p);

    virtual ~PatternObstacleManager();

private:
	std::vector<PatternObstacle> patterns;
};
