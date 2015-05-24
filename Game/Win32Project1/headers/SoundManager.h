#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include "FMOD/fmod.h"

class SoundManager
{
public:
	SoundManager();
	~SoundManager();
	int load_song(char *argv);
	void play();
	void pause();
	void reset();
	float* get_spectre(int nb_freq); // entry_hz = (44100 / 2) / nb_freq
	int* get_left_data();
	int* get_right_data();
	unsigned int get_length();
	unsigned int get_length_MS();
	int get_current_time_PCM(); // renvoi le temps en nombre de samples
	int get_current_time_MS();
	int getMSFromPCM(int pcm1024);	//transforme un PCM 1024 en sa valeur en ms dans la musique
	void set_current_time(int PCM);
	void change_pitch(float val); // change la vitesse de lecture
	float get_pitch();
private:
	FMOD_SYSTEM *system;
	FMOD_SOUND *musique;
	FMOD_CHANNEL* canal;

	int* data_left_channel;     // 16 premiers bits
	int* data_right_channel;    // 16 derniers bits
	float* spectre;
	unsigned int length;
	unsigned int length_MS;
	float pitch;
};

#endif // SOUNDMANAGER_H
