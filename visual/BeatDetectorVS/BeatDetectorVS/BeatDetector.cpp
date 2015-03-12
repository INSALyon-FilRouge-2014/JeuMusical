#include "BeatDetector.h"

#include <cmath>
#include <vector>

#define K_ENERGIE_RATIO  1.3 // le ratio entre les energie1024 et energie44100 pour la détection des peak d'energie
#define K_TRAIN_DIMP_SIZE 108 // la taille du train d'impulsions pour la convolution (en pack de 1024 (430=10sec))

using namespace std;

BeatDetector::BeatDetector(SoundManager* snd_mgr)
{
    this->snd_mgr = snd_mgr;
    length = snd_mgr->get_length();
    energie1024 = new float[length/1024];
    energie44100 = new float[length/1024];
    conv = new float[length/1024];
    beat = new float[length/1024];
    energie_peak = new float[length/1024+21];
    for(int i=0 ; i<length/1024+21 ; i++) energie_peak[i] = 0;
}

BeatDetector::~BeatDetector()
{

}

int BeatDetector::energie(int* data, int offset, int window)
{
    float energie=0.f;
    for(int i=offset ; (i<offset+window)&&(i<length) ; i++)
    {
        energie = energie + data[i]*data[i]/window;
    }
    return (int)energie;
}

void BeatDetector::normalize(float* signal, int size, float max_val)
{
    // recherche de la valeur max du signal
    float max=0.f;
    for(int i=0 ; i<size ; i++)
    {
        if (abs(signal[i])>max) max=abs(signal[i]);
    }
    // ajustage du signal
    float ratio = max_val/max;
    for(int i=0 ; i<size ; i++)
    {
        signal[i] = signal[i]*ratio;
    }
}

int BeatDetector::search_max(float* signal, int pos, int fenetre_half_size)
{
    float max=0.f;
    int max_pos=pos;
    for(int i=pos-fenetre_half_size ; i<=pos+fenetre_half_size ; i++)
    {
        if (signal[i]>max)
        {
            max=signal[i];
            max_pos=i;
        }
    }
    return max_pos;
}

void BeatDetector::audio_process(void)
{
// recupere les données de la musique
// ----------------------------------
    // le canal gauche
    int* data = snd_mgr->get_left_data();

// calcul des energies instantannées
// ---------------------------------
    for(int i=0 ; i<length/1024 ; i++)
    {
        energie1024[i] = energie(data, 1024*i, 4096); // 4096 pour lisser un peu la courbe
    }
// calcul des energies moyennes sur 1 seconde
// ------------------------------------------
    energie44100[0]=0;
    // la moyenne des 43 premiers energies1024 donne l'energie44100 de la premiere seconde
    float somme=0.f;
    for(int i=0 ; i<43 ; i++)
    {
        somme = somme + energie1024[i];
    }
    energie44100[0]=somme/43;

    // pour toutes les autres, ...
    for(int i=1 ; i<length/1024 ; i++)
    {
        somme = somme - energie1024[i-1] + energie1024[i+42];
        energie44100[i] = somme/43;
    }

// Ratio energie1024/energie44100
// ------------------------------
    for(int i=21 ; i<length/1024 ; i++)
    {
        // -21 pour centrer le energie1024 sur la seconde du energie44100
        if (energie1024[i]>K_ENERGIE_RATIO*energie44100[i-21])
        {
            energie_peak[i]=1;
        }
    }

// Calcul des BPMs
// ---------------
    // calcul des laps de temps entre chaque energie_peak
    vector<int> T;
    int i_prec=0;
    for(int i=1 ; i<length/1024 ; i++)
    {
        if((energie_peak[i]==1)&&(energie_peak[i-1]==0))
        {
            int di = i-i_prec;
            if (di>5) // rien pour les parasites
            {
                T.push_back(di);
                i_prec=i;
            }
        }
    }
    // le tableau T contient tous les laps de temps
    // fait des stats pour savoir quel est le plus fréquent
    int T_occ_max=0;
    float T_occ_moy=0.f;

        // compte les occurence de chaque laps de temps
    int occurences_T[86]; // max 2 paquets de 43 d'écart (2sec)
    for(int i=0 ; i<86 ; i++) occurences_T[i] = 0;
    for(int i=1 ; i<T.size() ; i++)
    {
        if(T[i]<=86) occurences_T[T[i]]++;
    }
    int occ_max=0;
    for(int i=1 ; i<86 ; i++)
    {
        if (occurences_T[i]>occ_max)
        {
            T_occ_max=i;
            occ_max = occurences_T[i];
        }
    }
        // on fait la moyenne du max + son max de voisin pour + de précision
    int voisin = T_occ_max-1;
    if (occurences_T[T_occ_max+1]>occurences_T[voisin]) voisin = T_occ_max+1;
    float div = occurences_T[T_occ_max] + occurences_T[voisin];

    if (div==0) T_occ_moy = 0;
    else T_occ_moy = (float)(T_occ_max*occurences_T[T_occ_max] + (voisin)*occurences_T[voisin]) / div;

    // clacul du tempo en BPMs
    tempo = (int)60.f/(T_occ_moy*(1024.f/44100.f));

// Calcul de la Beat line
// ----------------------
    // création d'un train d'impulsions (doit valoir 1 tous les T_occ_moy et 0 ailleurs)
    float train_dimp[K_TRAIN_DIMP_SIZE];
    float espace=0.f;
    train_dimp[0]=1.f;
    for(int i=1 ; i<K_TRAIN_DIMP_SIZE ; i++)
    {
        if (espace>=T_occ_moy)
        {
            train_dimp[i]=1;
            espace=espace-T_occ_moy; // on garde le depassement
        }
        else train_dimp[i]=0;
        espace+=1.f;
    }

    // convolution avec l'énergir instantannée de la music
    for(int i=0 ; i<length/1024-K_TRAIN_DIMP_SIZE ; i++)
    {
        for(int j=0 ; j<K_TRAIN_DIMP_SIZE ; j++)
        {
            conv[i] = conv[i] + energie1024[i+j] * train_dimp[j];
        }

    }
    normalize(conv, length/1024, 1.f);

    // recherche des peak de la conv
        // le max (c'est la plupart du temps un beat (pas tout le temps ...))
    for(int i=1 ; i<length/1024 ; i++)
        beat[i]=0;

    float max_conv=0.f;
    int max_conv_pos=0;
    for(int i=1 ; i<length/1024 ; i++)
    {
        if(conv[i]>max_conv)
        {
            max_conv=conv[i];
            max_conv_pos=i;
        }
    }
    beat[max_conv_pos]=1.f;

        // les suivants
            // vers la droite
    int i=max_conv_pos+T_occ_max;
    while((i<length/1024)&&(conv[i]>0.f))
    {
        // on cherche un max dans les parages
        int conv_max_pos_loc = search_max(conv, i, 2);
        beat[conv_max_pos_loc]=1.f;
        i=conv_max_pos_loc+T_occ_max;
    }
            // vers la gauche
    i=max_conv_pos-T_occ_max;
    while(i>0)
    {
        // on cherche un max dans les parages
        int conv_max_pos_loc = search_max(conv, i, 2);
        beat[conv_max_pos_loc]=1.f;
        i=conv_max_pos_loc-T_occ_max;
    }
}

float* BeatDetector::get_energie1024(void)
{
    return energie1024;
}

float* BeatDetector::get_energie44100(void)
{
    return energie44100;
}

float* BeatDetector::get_energie_peak(void)
{
    return energie_peak;
}

float* BeatDetector::get_conv()
{
    return conv;
}

float* BeatDetector::get_beat()
{
    return beat;
}

int BeatDetector::get_tempo(void)
{
    return tempo;
}
