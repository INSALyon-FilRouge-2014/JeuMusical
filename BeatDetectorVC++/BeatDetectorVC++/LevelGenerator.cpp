#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <string>

#include "LevelGenerator.h"

using namespace std;

LevelGenerator::LevelGenerator(BeatDetector* beat_dt, SoundManager* snd_mgr, string inputFileName)
{
	cout << endl;
	cout << "Constructeur du LevelGenerator" << endl;

	this->beat_dt = beat_dt;

	//r�cup�ration du  bpm flottant
	bpm = beat_dt->get_tempo_f();

	//calculs de la vitesse du niveau
	vitesse = BLOCKS_BY_BEAT / 60. * bpm;

	//r�cup�ration de la dur�e de la musique
	length_MS = snd_mgr->get_length_MS();

	//calcul du nombre de block qui peut composer la musique
	nbBlocks = vitesse * length_MS / 1000.;

	//r�cup�ration du nom de la musique
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
	cout << "Dur�e du niveau = " << length_MS << " ms (soit " << length_MS / 1000. << " s) (soit "<< length_MS/1000./60.<<" min)" << endl;
	cout << "Nombre de blocs du niveau = " << nbBlocks << " Blocks" << endl;
	cout << "Vitesse du niveau = " << vitesse << " Blocks/s" << endl;

	//autres id�es : 
	// d�finir la position des block en PCM !
	// comme on peut positionner la musique avec le PCM
	// on pourra synchro la musique a chaque bloc (tout les 4 blocs ?) au PCM du bloc
	//penser � analyser le tableau beat de taille LENGTH_PCM/1024
	cout << snd_mgr->get_length() << endl;
	int sum = 0;
	float* beats = beat_dt->get_beat();
	for (size_t i = 0; i < snd_mgr->get_length()/1024; i++)
	{
		if (beats[i] == 1.f)
		{
			sum++;
		}
	}
	cout << "Nombre de beats d�tect� : " << sum << endl;
	cout << "Nombre de beat th�orique (bpm*dur�e(min)): " << bpm*length_MS/1000/60 << endl;
	
}

void LevelGenerator::generateV1()
{
	//id�es : La majorit� des musique sont en tempo binaire (4/4 pour la plupart)
	//Pour placer les obstacles on peut donc regrouper 4 BEATS ensembles

}