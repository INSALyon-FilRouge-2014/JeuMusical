#include <iostream>
#include <cstdlib>
#include <vector>
#include <time.h>
#include "PatternObstacle.h"
#include "PatternObstacleManager.h"


using namespace std;

int main()
{
    /*
    PatternObstacle p;
    std::vector<PatternObstacle> v;
    PatternObstacleManager pm(v, 23903);
    pm.getRandomPattern(0,0,0,0);
    pm.getRandomPattern(0,0,0,0);
    pm.getRandomPattern(0,0,0,0);
    pm.getRandomPattern(0,0,0,0);
    cout << "Hello world!" << endl;
    */
    srand(time(NULL));
    cout << "rand : " << rand() << endl;
    cout << "rand : " << rand() << endl;
    cout << "rand : " << rand() << endl;
    cout << "rand : " << rand() << endl;
    return 0;
}
