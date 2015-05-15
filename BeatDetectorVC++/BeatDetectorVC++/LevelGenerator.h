#ifndef LEVELGENERATOR_H
#define LEVELGENERATOR_H

#include <vector>
#include "BeatDetector.h"
#include "SoundManager.h"
#include "Obstacle.h"
#include "XMLWriter.h"

//en block par beat
#define BLOCKS_BY_BEAT 2

class LevelGenerator
{
public:
	LevelGenerator(BeatDetector* beat_dt, SoundManager* snd_mgr, std::string inputFileName);
	~LevelGenerator();
	void generateV1();
	void generateV2();
	Obstacle** getTabObstacles(){ return tabObstacles; }

private:
	static const int HAUTEUR_SOL = 9;// la hauteur a laquelle sont positionnés les blocs de sol
	static const int HAUTEUR_PLAFOND = 1;//le plus haut bloc qu'on puisse poser
	static const int HAUTEUR_PERSO = 2;

	BeatDetector* beat_dt;
	XMLWriter* xml_writer;
	float bpm;			//en beat par seconde
	double vitesse;		//en block par seconde
	int nbObstacles;	//nombre d'obstacles présents dans le niveau
	int nbBlocks;		//nombre de blocks présents dans le niveau
	unsigned int length_MS; // longueur de la musique en ms
	unsigned int length_PCM; // longueur de la musique en PCM (echantillons)
	Obstacle** tabObstacles;	//tableau de la taille du morceau contenant des NULL ou un obstacle s'il y en a un
	std::string musicName;
	std::vector<Obstacle> obstList;
};

#endif // LEVELGENERATOR_H
