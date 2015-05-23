#include <iostream>
#include <vector>
#include "PatternObstacle.h"

class PatternObstacleManager
{
public:
    void addPatternObstacle(PatternObstacle pat);

	PatternObstacle getRandomPattern(int length, int start_height);

	void loadPatterns();

	PatternObstacleManager(int seed);

	PatternObstacleManager(int seed, std::vector<PatternObstacle> p);

    virtual ~PatternObstacleManager();

private:
	std::vector<PatternObstacle> patterns;
};
