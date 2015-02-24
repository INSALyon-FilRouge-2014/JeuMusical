#include "Scene.h"

#include "FMOD/fmod.h"
#include <sstream>
#include <cmath>


#define K_GRAVITE 0.81

Scene::Scene(RenderWindow* App, SoundManager* snd_mgr, BeatDetector* beatdec, char *argv)
{
    this->App = App;
    this->snd_mgr = snd_mgr;
    this->beatdec = beatdec;

    window = 430; // (44100/1024)*10sec
    offset = 0;

    float* data1024=beatdec->get_energie1024();
    float* data44100=beatdec->get_energie44100();
    float* energie_peak = beatdec->get_energie_peak();
    float* conv = beatdec->get_conv();
    float* beat = beatdec->get_beat();

    int data_index = 0;
    for (int i=0 ; i<800 ; i++)
    {
        data_index = i*window/800;
        green[i].AddPoint(-400+i, 300, sf::Color::Green);
        green[i].AddPoint(-399+i, 300, sf::Color::Green);
        green[i].AddPoint(-399+i, 300-data1024[data_index]/1000000, sf::Color::Green);
        green[i].AddPoint(-400+i, 300-data1024[data_index]/1000000, sf::Color::Green);
        blue[i].AddPoint(-400+i, 300, sf::Color(0,0,105,180));
        blue[i].AddPoint(-399+i, 300, sf::Color(0,0,105,180));
        blue[i].AddPoint(-399+i, 300-data44100[data_index]/1000000, sf::Color(0,0,255,150));
        blue[i].AddPoint(-400+i, 300-data44100[data_index]/1000000, sf::Color(0,0,255,150));
        yellow[i].AddPoint(-400+i, 300, sf::Color::Yellow);
        yellow[i].AddPoint(-399+i, 300, sf::Color::Yellow);
        yellow[i].AddPoint(-399+i, 300-100*conv[data_index], sf::Color::Yellow);
        yellow[i].AddPoint(-400+i, 300-100*conv[data_index], sf::Color::Yellow);
        white[i].AddPoint(-400+i, 0, sf::Color::White);
        white[i].AddPoint(-399+i, 0, sf::Color::White);
        white[i].AddPoint(-399+i, -10*energie_peak[data_index], sf::Color::White);
        white[i].AddPoint(-400+i, -10*energie_peak[data_index], sf::Color::White);
        dark_green[i].AddPoint(-400+i, 0, sf::Color(0,105,0,180));
        dark_green[i].AddPoint(-399+i, 0, sf::Color(0,105,0,180));
        dark_green[i].AddPoint(-399+i, -100* beat[data_index], sf::Color(0,105,0,180));
        dark_green[i].AddPoint(-400+i, -100* beat[data_index], sf::Color(0,105,0,180));
    }
    current_line = sf::Shape::Line(-399, -300, -399, 300, 2, sf::Color::White);
    beat_light = sf::Shape::Circle(0,0,30,sf::Color(120, 250, 250,255));
    hight=100.f;

    // construction de la string du temps total
    float total_time = (float)(snd_mgr->get_length()/44100.f);
    int minutes = (int)total_time/60;
    int secondes = (int)total_time-(60*minutes);
    if (minutes<10) total_time_string << "0";
    total_time_string << minutes << ":";
    if (secondes <10) total_time_string << "0";
    total_time_string << secondes;

    // consreuction de la string des instructions
    instructions_text.SetText("Play/Pause: P\nReset: R\nScroll: (Ctrl) ArrowKey\nSpeed: +/-\nClick to set position");

    // positionnement des textes
    time_text.SetPosition(-400, -300);
    tempo_text.SetPosition(-400, -270);
    speed_text.SetPosition(-400, -240);
    instructions_text.SetPosition(0, -300);
}

Scene::~Scene()
{
}

void Scene::draw()
{
    // recupere le temps courant
    float time = (float)(snd_mgr->get_current_time_PCM()/44100.f);

    for (int i=0 ; i<800 ; i++)
    {
        App->Draw(green[i]);
        App->Draw(blue[i]);
        App->Draw(yellow[i]);
        App->Draw(dark_green[i]);
        App->Draw(white[i]);
    }
    current_line.SetPosition(-(offset/(float)44100)*800/(window/43)+time*800/(window/43),0);
    App->Draw(current_line);

    float* beat = beatdec->get_beat();

    // saut dynamique de la beat_light
        // verifie ou sont les beats les plus proches
    float current_pos = snd_mgr->get_current_time_PCM()/1024.f;
            // celui de gauche
    bool found = false;
    int lower_pos=(int)current_pos+1;
    while (found==false)
    {
        lower_pos--;
        if(beat[lower_pos]>0) found=true;
    }
            // celui de droite
    found = false;
    int upper_pos=(int)current_pos-1;
    while (found==false)
    {
        upper_pos++;
        if(beat[upper_pos]>0) found=true;
    }
        // calcul de la hauteur
    int L=upper_pos-lower_pos; // la distance a sauter
    float t=current_pos-(float)lower_pos; // le temps ecoulé depuis le debut du saut
    hight = -(K_GRAVITE/2)*t*t+(K_GRAVITE/2)*L*t; // equation de cinematique

    beat_light.SetY(beat_light.GetPosition().y-hight);
    beat_light.SetX(-400-(offset/(float)44100)*800/(window/43)+time*800/(window/43));
    App->Draw(beat_light);
    beat_light.SetY(0);

    // Construction et affichage des strings
         // le time
    float current_time = (float)(snd_mgr->get_current_time_PCM()/44100.f);
    int minutes = (int)current_time/60;
    int secondes = (int)current_time-(60*minutes);
    std::ostringstream current_time_string;
    if (minutes<10) current_time_string << "0";
    current_time_string << minutes << ":";
    if (secondes <10) current_time_string << "0";
    current_time_string << secondes;

    time_text.SetText(current_time_string.str()+"/"+total_time_string.str());
    App->Draw(time_text);
        // la speed
    std::ostringstream speed_string;
    speed_string << "speed: x" << snd_mgr->get_pitch();
    speed_text.SetText(speed_string.str());
    App->Draw(speed_text);
        // le tempo
    std::ostringstream tempo_string;
    tempo_string << "tempo:" << snd_mgr->get_pitch()*beatdec->get_tempo() << " BPM";
    tempo_text.SetText(tempo_string.str());
    App->Draw(tempo_text);
        //les instructions
    App->Draw(instructions_text);
}

void Scene::shift(int factor)
{
    offset+=factor;
    if (offset<0) offset=0;
    redraw();
}

void Scene::extend(int factor)
{
    window+=factor;
    if (window<43) window = 43;
    redraw();
}

void Scene::goto_pos(int X)
{
    int pos = X*window/800+offset/1024;
    snd_mgr->set_current_time(pos*1024);
}

void Scene::redraw()
{
    float* data1024=beatdec->get_energie1024();
    float* data44100=beatdec->get_energie44100();
    float* energie_peak = beatdec->get_energie_peak();
    float* conv = beatdec->get_conv();
    float* beat = beatdec->get_beat();
    int length = snd_mgr->get_length();

    int data_index = 0;
    for (int i=0 ; (i<800)&&(data_index<length/1024) ; i++)
    {
        data_index = i*window/800+offset/1024;
        green[i].SetPointPosition(2, -399+i, 300-data1024[data_index]/1000000);
        green[i].SetPointPosition(3, -400+i, 300-data1024[data_index]/1000000);
        blue[i].SetPointPosition(2, -399+i, 300-data44100[-21+data_index]/1000000);
        blue[i].SetPointPosition(3, -400+i, 300-data44100[-21+data_index]/1000000);
        yellow[i].SetPointPosition(2, -399+i, 300-100*conv[data_index]);
        yellow[i].SetPointPosition(3, -400+i, 300-100*conv[data_index]);
        dark_green[i].SetPointPosition(2, -399+i, -100* beat[data_index]);
        dark_green[i].SetPointPosition(3, -400+i, -100* beat[data_index]);
        white[i].SetPointPosition(2, -399+i, -10*energie_peak[data_index]);
        white[i].SetPointPosition(3, -400+i, -10*energie_peak[data_index]);
    }
}
