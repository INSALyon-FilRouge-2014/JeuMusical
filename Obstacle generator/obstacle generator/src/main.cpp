#include <iostream>
#include <cstdlib>
#include <vector>
#include <time.h>
#include "PatternObstacle.h"
#include "PatternObstacleManager.h"


using namespace std;

int main()
{

    cout << "Creation du PatternObstacleManager ..." << endl;
    PatternObstacleManager POM(12343);
    cout << "Chargement des patterns ..." <<endl;
    POM.loadPatterns();
    cout << "Selection pseudo-aleatoire d'un pattern"<< endl;

    int mesure = 4;
    int start_height = 5;

    PatternObstacle p = POM.getRandomPattern(mesure, start_height);
    p.display();
    start_height = p.getEndHeight();

    p = POM.getRandomPattern(mesure, start_height);
    p.display();
    start_height = p.getEndHeight();

    p = POM.getRandomPattern(mesure, start_height);
    p.display();
    start_height = p.getEndHeight();

    p = POM.getRandomPattern(mesure, start_height);
    p.display();
    start_height = p.getEndHeight();

    p = POM.getRandomPattern(mesure, start_height);
    p.display();
    start_height = p.getEndHeight();

    p = POM.getRandomPattern(mesure, start_height);
    p.display();
    start_height = p.getEndHeight();

    p = POM.getRandomPattern(mesure, start_height);
    p.display();
    start_height = p.getEndHeight();

    p = POM.getRandomPattern(mesure, start_height);
    p.display();
    start_height = p.getEndHeight();


/*
    p1.display();
    printf("Denivelee : %d \n",p1.getDenivelee());
    printf("DownDistance : %d \n",p1.getDownDistance());
    printf("UpDistance : %d \n",p1.getUpDistance());
    printf("EndHeight : %d \n",p1.getEndHeight());
    printf("Length : %d \n\n",p1.getLength());

    printf("Setting Start Height at 4 ...\n");
    p1.setStartHeight(4);

    p1.display();
    printf("Denivelee : %d \n",p1.getDenivelee());
    printf("DownDistance : %d \n",p1.getDownDistance());
    printf("UpDistance : %d \n",p1.getUpDistance());
    printf("EndHeight : %d \n",p1.getEndHeight());
    printf("Length : %d \n\n",p1.getLength());
*/
    return 0;
}
