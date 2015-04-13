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

	float* data1024 = beatdec->get_energie1024();
	float* data44100 = beatdec->get_energie44100();
	float* energie_peak = beatdec->get_energie_peak();
	float* conv = beatdec->get_conv();
	float* beat = beatdec->get_beat();

	int data_index = 0;
	for (int i = 0; i<800; i++)
	{
		data_index = i*window / 800;

		green[i].setPointCount(4);
		green[i].setPoint(0, sf::Vector2f(-400 + i, 300));
		green[i].setPoint(1, sf::Vector2f(-399 + i, 300));
		green[i].setPoint(2, sf::Vector2f(-399 + i, 300 - data1024[data_index] / 1000000));
		green[i].setPoint(3, sf::Vector2f(-400 + i, 300 - data1024[data_index] / 1000000));
		green[i].setFillColor(sf::Color::Green);

		blue[i].setPointCount(4);
		blue[i].setPoint(0, sf::Vector2f(-400 + i, 300));
		blue[i].setPoint(1, sf::Vector2f(-399 + i, 300));
		blue[i].setPoint(2, sf::Vector2f(-399 + i, 300 - data44100[data_index] / 1000000));
		blue[i].setPoint(3, sf::Vector2f(-400 + i, 300 - data44100[data_index] / 1000000));
		blue[i].setFillColor(sf::Color(0, 0, 255, 150));

		yellow[i].setPointCount(4);
		yellow[i].setPoint(0, sf::Vector2f(-400 + i, 300));
		yellow[i].setPoint(1, sf::Vector2f(-399 + i, 300));
		yellow[i].setPoint(2, sf::Vector2f(-399 + i, 300 - 100 * conv[data_index]));
		yellow[i].setPoint(3, sf::Vector2f(-400 + i, 300 - 100 * conv[data_index]));
		yellow[i].setFillColor(sf::Color::Yellow);

		white[i].setPointCount(4);
		white[i].setPoint(0, sf::Vector2f(-400 + i, 300));
		white[i].setPoint(1, sf::Vector2f(-399 + i, 300));
		white[i].setPoint(2, sf::Vector2f(-399 + i, -10 * energie_peak[data_index]));
		white[i].setPoint(3, sf::Vector2f(-400 + i, -10 * energie_peak[data_index]));
		white[i].setFillColor(sf::Color::White);

		dark_green[i].setPointCount(4);
		dark_green[i].setPoint(0, sf::Vector2f(-400 + i, 300));
		dark_green[i].setPoint(1, sf::Vector2f(-399 + i, 300));
		dark_green[i].setPoint(2, sf::Vector2f(-399 + i, -100 * beat[data_index]));
		dark_green[i].setPoint(3, sf::Vector2f(-400 + i, -100 * beat[data_index]));
		dark_green[i].setFillColor(sf::Color(0, 105, 0, 180));


	}

	current_line = sf::RectangleShape(sf::Vector2f(1, 600));
	current_line.setFillColor(sf::Color::White);
	current_line.setPosition(sf::Vector2f(-399, 300));

	beat_light = sf::CircleShape(30.0F);
	beat_light.setFillColor(sf::Color(120, 250, 250, 255));
	beat_light.setPosition(sf::Vector2f(0, 0));
	hight = 100.f;

	// construction de la string du temps total
	float total_time = (float)(snd_mgr->get_length() / 44100.f);
	int minutes = (int)total_time / 60;
	int secondes = (int)total_time - (60 * minutes);
	if (minutes<10) total_time_string << "0";
	total_time_string << minutes << ":";
	if (secondes <10) total_time_string << "0";
	total_time_string << secondes;

	// construction de la string des instructions
	instructions_text.setString("Play/Pause: P\nReset: R\nScroll: (Ctrl) ArrowKey\nSpeed: +/-\nClick to set position");

	// positionnement des textes
	time_text.setPosition(-400, -300);
	tempo_text.setPosition(-400, -270);
	speed_text.setPosition(-400, -240);
	instructions_text.setPosition(0, -300);
}

Scene::~Scene()
{
}

void Scene::draw()
{
	// recupere le temps courant
	float time = (float)(snd_mgr->get_current_time_PCM() / 44100.f);

	for (int i = 0; i<800; i++)
	{
		App->draw(green[i]);
		App->draw(blue[i]);
		App->draw(yellow[i]);
		App->draw(dark_green[i]);
		App->draw(white[i]);
	}
	current_line.setPosition(-(offset / (float)44100) * 800 / (window / 43) + time * 800 / (window / 43), 0);
	App->draw(current_line);

	float* beat = beatdec->get_beat();

	// saut dynamique de la beat_light
	// verifie ou sont les beats les plus proches
	float current_pos = snd_mgr->get_current_time_PCM() / 1024.f;
	// celui de gauche
	bool found = false;
	int lower_pos = (int)current_pos + 1;
	while (found == false)
	{
		lower_pos--;
		if (beat[lower_pos]>0) found = true;
	}
	// celui de droite
	found = false;
	int upper_pos = (int)current_pos - 1;
	while (found == false)
	{
		upper_pos++;
		if (beat[upper_pos]>0) found = true;
	}
	// calcul de la hauteur
	int L = upper_pos - lower_pos; // la distance a sauter
	float t = current_pos - (float)lower_pos; // le temps ecoulé depuis le debut du saut
	hight = -(K_GRAVITE / 2)*t*t + (K_GRAVITE / 2)*L*t; // equation de cinematique

	beat_light.setPosition(sf::Vector2f(-400 - (offset / (float)44100) * 800 / (window / 43) + time * 800 / (window / 43), beat_light.getPosition().y - hight));
	App->draw(beat_light);
	beat_light.setPosition(sf::Vector2f(-400 - (offset / (float)44100) * 800 / (window / 43) + time * 800 / (window / 43), 0));
	//beat_light.SetY(0);

	// Construction et affichage des strings
	// le time
	float current_time = (float)(snd_mgr->get_current_time_PCM() / 44100.f);
	int minutes = (int)current_time / 60;
	int secondes = (int)current_time - (60 * minutes);
	std::ostringstream current_time_string;
	if (minutes<10) current_time_string << "0";
	current_time_string << minutes << ":";
	if (secondes <10) current_time_string << "0";
	current_time_string << secondes;

	time_text.setString(current_time_string.str() + "/" + total_time_string.str());
	App->draw(time_text);
	// la speed
	std::ostringstream speed_string;
	speed_string << "speed: x" << snd_mgr->get_pitch();
	speed_text.setString(speed_string.str());
	App->draw(speed_text);
	// le tempo
	std::ostringstream tempo_string;
	tempo_string << "tempo:" << snd_mgr->get_pitch()*beatdec->get_tempo() << " BPM";
	tempo_text.setString(tempo_string.str());
	App->draw(tempo_text);
	//les instructions
	App->draw(instructions_text);
}

void Scene::shift(int factor)
{
	offset += factor;
	if (offset<0) offset = 0;
	redraw();
}

void Scene::extend(int factor)
{
	window += factor;
	if (window<43) window = 43;
	redraw();
}

void Scene::goto_pos(int X)
{
	int pos = X*window / 800 + offset / 1024;
	snd_mgr->set_current_time(pos * 1024);
}

void Scene::redraw()
{
	float* data1024 = beatdec->get_energie1024();
	float* data44100 = beatdec->get_energie44100();
	float* energie_peak = beatdec->get_energie_peak();
	float* conv = beatdec->get_conv();
	float* beat = beatdec->get_beat();
	int length = snd_mgr->get_length();

	int data_index = 0;
	for (int i = 0; (i<800) && (data_index<length / 1024); i++)
	{
		data_index = i*window / 800 + offset / 1024;
		green[i].setPoint(2, sf::Vector2f(-399 + i, 300 - data1024[data_index] / 1000000));
		green[i].setPoint(3, sf::Vector2f(-400 + i, 300 - data1024[data_index] / 1000000));
		blue[i].setPoint(2, sf::Vector2f(-399 + i, 300 - data44100[-21 + data_index] / 1000000));
		blue[i].setPoint(3, sf::Vector2f(-400 + i, 300 - data44100[-21 + data_index] / 1000000));
		yellow[i].setPoint(2, sf::Vector2f(-399 + i, 300 - 100 * conv[data_index]));
		yellow[i].setPoint(3, sf::Vector2f(-400 + i, 300 - 100 * conv[data_index]));
		dark_green[i].setPoint(2, sf::Vector2f(-399 + i, -100 * beat[data_index]));
		dark_green[i].setPoint(3, sf::Vector2f(-400 + i, -100 * beat[data_index]));
		white[i].setPoint(2, sf::Vector2f(-399 + i, -10 * energie_peak[data_index]));
		white[i].setPoint(3, sf::Vector2f(-400 + i, -10 * energie_peak[data_index]));
	}
}
