
#include <sstream>
#include <fstream>
#include <iostream>

#include "SoundManager.h"
#include "BeatDetector.h"
#include "LevelGenerator.h"

using namespace std;

int main(int argc, char *argv[])
{
	cout << "Fichier "  << argv[1] << endl;
	ifstream mamusique(argv[1]);
	if (mamusique.good())
	{
		cout << "Fichier trouve" << endl;
		mamusique.close();
	}
	else
	{
		cout << "Fichier introuvable" << endl;
		return EXIT_FAILURE;
	}

	// Create SoundManager
	SoundManager* snd_mng = new SoundManager();
	snd_mng->load_song(argv[1]); // load song in arguments
	snd_mng->play();
	snd_mng->pause();

	// Create BeatDetector
	BeatDetector* beatdec = new BeatDetector(snd_mng);
	beatdec->audio_process(); // launch beats detection

	LevelGenerator * lvlGen = new LevelGenerator(beatdec, snd_mng, string(argv[1]));
	lvlGen->generateV1();

	system("pause");


	//affichage des beats
	float* beat = beatdec->get_beat();
	Obstacle** tabObstacles = lvlGen->getTabObstacles();
	int currentPos;
	bool inBeat = false;
	int beatCounter = 0;
	snd_mng->pause();
	while (true)
	{
		currentPos = snd_mng->get_current_time_PCM() / 1024.f;
		//if (beat[currentPos] > 0)
		//	cout << beat[currentPos] << endl;
		if (beat[currentPos] > 0 && inBeat == false)//on entre dans un beat
		{
			inBeat = true;
			cout << "BEAT ! no" << beatCounter;
			if (tabObstacles[currentPos] != NULL)
				cout << " -- OBSTACLE ! ";
			cout << endl;
			beatCounter++;
		}
		else if (beat[currentPos] < 1 && inBeat == true)
		{
			inBeat = false;
			//cout << beat[currentPos] << endl;
		}
	}
	return EXIT_SUCCESS;
}


