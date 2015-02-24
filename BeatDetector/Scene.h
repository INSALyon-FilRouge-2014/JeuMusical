#ifndef Scene_H
#define Scene_H

#include "SoundManager.h"
#include "BeatDetector.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <sstream>
#include <iostream>


using namespace sf;
using namespace std;

class Scene
{
    public:
        Scene(RenderWindow* App, SoundManager* snd_mgr, BeatDetector* beadec, char *argv);
        ~Scene();
        void draw();

        void extend(int factor);
        void shift(int factor);
        void goto_pos(int X);

        void redraw();

    private:
        RenderWindow* App;
        SoundManager* snd_mgr;
        BeatDetector* beatdec;

        sf::Shape green[800];
        sf::Shape blue[800];
        sf::Shape yellow[800];
        sf::Shape white[800];
        sf::Shape dark_green[800];
        sf::Shape current_line;
        int window; // le nombre de data affichées
        int offset;  // la premiere data affichée

        sf::Shape beat_light;
        float hight;

        std::ostringstream total_time_string;
        sf::String time_text;
        sf::String tempo_text;
        sf::String speed_text;
        sf::String instructions_text;
};

#endif // Scene_H
