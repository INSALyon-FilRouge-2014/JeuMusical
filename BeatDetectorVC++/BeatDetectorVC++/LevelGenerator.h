#ifndef LEVELGENERATOR_H
#define LEVELGENERATOR_H

#include <vector>
#include "BeatDetector.h"
#include "SoundManager.h"
#include "Obstacle.h"

//en block par beat
#define BLOCKS_BY_BEAT 4

class LevelGenerator
{
public:
	LevelGenerator(BeatDetector* beat_dt, SoundManager* snd_mgr, std::string inputFileName);
	~LevelGenerator();
	void generateV1();

private:
	BeatDetector* beat_dt;
	float bpm;			//en beat par seconde
	double vitesse;		//en block par seconde
	int nbObstacles;	//nombre d'obstacles présents dans le niveau
	int nbBlocks;		//nombre de blocks présents dans le niveau
	unsigned int length_MS; // longueur de la musique en ms
	std::string musicName;
	std::vector<Obstacle> obstList;

};

#endif // LEVELGENERATOR_H
