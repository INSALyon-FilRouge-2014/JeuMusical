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

	sf::ConvexShape green[800];
	sf::ConvexShape blue[800];
	sf::ConvexShape yellow[800];
	sf::ConvexShape white[800];
	sf::ConvexShape dark_green[800];
	sf::RectangleShape current_line;
	int window; // le nombre de data affichées
	int offset;  // la premiere data affichée

	sf::CircleShape beat_light;
	float hight;

	std::ostringstream total_time_string;
	sf::Text time_text;
	sf::Text tempo_text;
	sf::Text speed_text;
	sf::Text instructions_text;
};

#endif // Scene_H
