#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <string>

#include "LevelGenerator.h"
#include "PatternObstacleManager.h"
#include "PatternObstacle.h"

using namespace std;

LevelGenerator::LevelGenerator(BeatDetector* beat_dt, SoundManager* snd_mgr, string inputFileName)
{
	cout << endl;
	cout << "Constructeur du LevelGenerator" << endl;

	this->beat_dt = beat_dt;
	//récupération du  bpm flottant
	bpm = beat_dt->get_tempo_f();

	//calculs de la vitesse du niveau
	vitesse = BLOCKS_BY_BEAT / 60. * bpm;

	//récupération de la durée de la musique
	length_MS = snd_mgr->get_length_MS();

	//récupération de la durée de la musique
	length_PCM = snd_mgr->get_length();
	
	//calcul du nombre de block qui peut composer la musique
	nbBlocks = vitesse * (length_MS / 1000.);

	//récupération du nom de la musique
	musicName = inputFileName;
	size_t ext_pos = musicName.find_last_of('.');
	if (ext_pos != string::npos)
	{
		size_t path_pos = musicName.find_last_of('/');
		if (path_pos != string::npos)
		{
			musicName = musicName.substr(path_pos + 1, ext_pos-path_pos-1);
		}
		else
		{
			path_pos = musicName.find_last_of('\\');
			if (path_pos != string::npos)
			{
				musicName = musicName.substr(path_pos + 1, ext_pos-path_pos-1);
			}
		}
	}
	

	//affichage des informations
	cout << "Nom du niveau :" << musicName << endl;
	cout << "BPM du niveau = " << bpm << " Beat/min" << endl;
	cout << "Durée du niveau = " << length_MS << " ms (soit " << length_MS / 1000. << " s) (soit "<< length_MS/1000./60.<<" min)" << endl;
	cout << "Durée du niveau en PCM = " << length_PCM << " PCM" << endl;
	cout << "Durée du niveau en PCM (par groupe de 1024) = " << length_PCM/1024 << " PCM" << endl;
	cout << "Nombre de blocs du niveau = " << nbBlocks << " Blocks" << endl;
	cout << "Vitesse du niveau = " << vitesse << " Blocks/s" << endl;

	//autres idées : 
	// définir la position des block en PCM !
	// comme on peut positionner la musique avec le PCM
	// on pourra synchro la musique a chaque bloc (tout les 4 blocs ?) au PCM du bloc
	// penser à analyser le tableau beat de taille LENGTH_PCM/1024
	int sum = 0;
	float* beats = beat_dt->get_beat();
	for (size_t i = 0; i < length_PCM / 1024; i++)
	{
		if (beats[i] == 1.f)
		{
			sum++;
		}
	}
	cout << "Nombre de beats détectés : " << sum << endl;
	cout << "Nombre de beat théorique (bpm*durée(min)) : " << bpm*length_MS/1000/60 << endl;
	
	//initialisation du tableau des obstacles
	PCMtoMS = new int[length_PCM / 1024];
	tabObstacles = new Obstacle*[length_PCM / 1024];
	for (int i = 0; i < length_PCM / 1024; i++)
	{
		tabObstacles[i] = NULL;
		PCMtoMS[i] = snd_mgr->getMSFromPCM(i);
	}

	//choix de la seed par rapport a la taille PCM de la musique
	int seed = this->length_PCM;

	//configuration du PatternObstacleManager
	cout << "Configuration du générateur ... seed : " << seed << endl;
	POM = new PatternObstacleManager(seed);
	POM->loadPatterns();
	cout << POM->countLoadedPattern() << " patterns ont ete charges." << endl;

	//création du fichier xml
	this->xml_writer = new XMLWriter(musicName+".xml",musicName,nbBlocks, bpm, vitesse);
}


LevelGenerator::~LevelGenerator()
{
	delete xml_writer;
	delete POM;
}

void LevelGenerator::generateV1()
{
	int currentHeight = 0;
	int currentPos = 0;
	int mesureCounter = 0;
	int beatCounter = 0;
	// Idées : La majorité des musiques sont en tempo binaire (4/4 pour la plupart)
	// Pour placer les obstacles on peut donc regrouper 4 BEATS ensembles

	// On commence par laisser le temps à l'utilisateur ~5s
	// Positionnement du premier obstacle

	float* beats = beat_dt->get_beat();
	//parcours de tous les beats :
	for (unsigned int i = 0; i < length_PCM / 1024; i++)
		//i est ici l'indice mais egalement la position en PCM1024
	{
		if (beats[i] == 1.f)
		{
			//situé sur un beat
			if (beatCounter % 4 == 0)	// tous les 4 beat on demarre une nouvelle mesure.
			{
				// Au debut d'une mesure
				Obstacle ob(beatCounter*BLOCKS_BY_BEAT, i * 1024, PCMtoMS[i], 8, Obstacle::CAISSE);
				obstList.push_back(ob);
				tabObstacles[i] = &ob;
				xml_writer->writeObstacle(ob);
				mesureCounter++;
			}
			beatCounter++;
		}
	}
}


void LevelGenerator::generateV2()
{
	int currentHeight = 0;
	int currentPos = 0;
	int mesureCounter = 0;
	unsigned int beatCounter = 0;
	// Idées : La majorité des musiques sont en tempo binaire (4/4 pour la plupart)
	// Pour placer les obstacles on peut donc regrouper 4 BEATS ensembles


	// On commence par laisser le temps à l'utilisateur 4 Mesures
	// Positionnement du premier obstacle
	float* beats = beat_dt->get_beat();

	unsigned int i = 0;
	while (beatCounter <= 15)
	{
		if (beats[i] == 1.f)
		{
			beatCounter++;
		}
		i++;
	}


	//parcours de tous les beats suivants :
	for (; i < length_PCM / 1024; i++)
		//i est ici l'indice mais egalement la position en PCM1024
	{
		if (beats[i] == 1.f)
		{
			//situé sur un beat
			if (beatCounter % 4 == 0)	// tous les 4 beat on demarre une nouvelle mesure.
			{
				// Au debut d'une mesure
				Obstacle ob(beatCounter*BLOCKS_BY_BEAT, i * 1024, PCMtoMS[i], 8, Obstacle::CAISSE);
				obstList.push_back(ob);
				tabObstacles[i] = &ob;
				xml_writer->writeObstacle(ob);
				mesureCounter++;
			}
			beatCounter++;
		}
	}
}

void LevelGenerator::generateV3()
{
	int currentHeight = 0;
	int currentPos = 0;
	int mesureCounter = 0;
	unsigned int beatCounter = 0;
	// Idées : La majorité des musiques sont en tempo binaire (4/4 pour la plupart)
	// Pour placer les obstacles on peut donc regrouper 4 BEATS ensembles


	// On commence par laisser le temps à l'utilisateur 4 Mesures
	// Positionnement du premier obstacle
	float* beats = beat_dt->get_beat();

	unsigned int i = 0;
	while (beatCounter <= 15)
	{
		if (beats[i] == 1.f)
		{
			beatCounter++;
		}
		i++;
	}


	int mesure_length = 4;
	int start_height = Obstacle::H_SOL-1;	//on demarre juste au dessus du sol
	cout << start_height;
	int num_beat = 0;
	PatternObstacle pat;
	//parcours de tous les beats suivants :
	for (; i < length_PCM / 1024; i++)
		//i est ici l'indice mais egalement la position en PCM1024
	{
		if (beats[i] == 1.f)
		{
			//situé sur un beat
			num_beat = beatCounter % 4;
			if (num_beat == 0)	// tous les 4 beat on demarre une nouvelle mesure.
			{
				// Au debut d'une mesure
				//on essaye de placer
				pat = POM->getRandomPattern(mesure_length, start_height);
				//pat.display();
				start_height = pat.getEndHeight();
				cout << " > " << start_height;
				mesureCounter++;
			}
			//chaque beat on récupère le vecteur d'obstacle lui correspondant dans le pattern			
			vector<Obstacle> vec = pat.getObstacles()[num_beat];
			
			//si il y a des obstacles pour ce beat
			for (auto it_vec = vec.begin(); it_vec != vec.end(); ++it_vec)
			{
				//on déroule les obstacles de ce beat
				it_vec->setPositions(beatCounter*BLOCKS_BY_BEAT, i * 1024, PCMtoMS[i]);
				obstList.push_back(*it_vec);
				xml_writer->writeObstacle(*it_vec);

				it_vec->setPositions(beatCounter*BLOCKS_BY_BEAT+1, i * 1024, PCMtoMS[i]);
				obstList.push_back(*it_vec);
				xml_writer->writeObstacle(*it_vec);
			}

			
			tabObstacles[i] = new Obstacle(0, Obstacle::CAISSE);
			beatCounter++;
		}
	}
}

