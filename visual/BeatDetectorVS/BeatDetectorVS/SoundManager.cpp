#include "SoundManager.h"

#include <cmath>
#include <stdio.h>

using namespace std;

SoundManager::SoundManager()
{
	FMOD_System_Create(&system);
	FMOD_System_Init(system, 1, FMOD_INIT_NORMAL, NULL);
    canal = NULL;
    pitch=1.f;
}

SoundManager::~SoundManager()
{
    FMOD_System_Release(system);
}

int SoundManager::load_song(char *argv)
{
    /* On ouvre la musique */
	FMOD_System_CreateSound(system, argv, FMOD_SOFTWARE | FMOD_2D , 0, &musique);

	/* On active la répétition de la musique à l'infini */
	FMOD_Sound_SetLoopCount(musique, -1);
	FMOD_Sound_GetLength(musique, &length, FMOD_TIMEUNIT_PCM);

	/* on rempli les tableau data_left et data_right avec les données du buffer */
    void* ptr1;
    void* ptr2;             // ???
    unsigned int length1;   // ???
    unsigned int length2;   // ???
    data_left_channel = new int[length];
    data_right_channel = new int[length];
    FMOD_Sound_Lock(musique, 0, length, &ptr1, &ptr2, &length1, &length2);
    for (int i=0 ; i<length ; i++)
    {
        data_left_channel[i] = ((int*)ptr1)[i]>>16;
        data_right_channel[i] = (((int*)ptr1)[i]<<16)>>16;
    }
    FMOD_Sound_Unlock(musique, ptr1, ptr2, length, length2);
    return 0;
}

void SoundManager::play(void)
{
    FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, musique, 0, NULL);
	FMOD_System_GetChannel(system, 0, &canal);
}

void SoundManager::pause(void)
{
        FMOD_BOOL etat;
        FMOD_Channel_GetPaused(canal, &etat);
        FMOD_Channel_SetFrequency(canal, 44100.f*pitch);
        if (etat == 1) // Si la chanson est en pause
            FMOD_Channel_SetPaused(canal, 0); // On enlève la pause
        else // Sinon, elle est en cours de lecture
            FMOD_Channel_SetPaused(canal, 1); // On met en pause
}

void SoundManager::reset(void)
{
    FMOD_Channel_SetPosition(canal, 0, FMOD_TIMEUNIT_PCM);
}

int* SoundManager::get_left_data()
{
    return data_left_channel;
}

int* SoundManager::get_right_data()
{
    return data_right_channel;
}

unsigned int SoundManager::get_length()
{
    return length;
}

int SoundManager::get_current_time_PCM()
{
    unsigned int pos=0;
    FMOD_Channel_GetPosition(canal,&pos,FMOD_TIMEUNIT_PCM);
    return pos;
}

void SoundManager::set_current_time(int PCM)
{
    FMOD_Channel_SetPosition(canal,PCM,FMOD_TIMEUNIT_PCM);
}

void SoundManager::change_pitch(float val)
{
    pause();
    pitch+=val;
    pause();
}

float SoundManager::get_pitch()
{
    return pitch;
}
