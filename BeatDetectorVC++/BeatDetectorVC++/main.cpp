#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <sstream>
#include <fstream>

#include "SoundManager.h"
#include "Scene.h"
#include "BeatDetector.h"
#include "LevelGenerator.h"


int main(int argc, char *argv[])
{
	cout << "coucou : fichier "  << argv[1] << endl;
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

	// Create main window
	//sf::RenderWindow App(sf::VideoMode(800, 600), "Beat detector");
	//sf::Vector2<int> initPos(0, 0);
	//App.setPosition(initPos);
	//App.setMouseCursorVisible(false);

	// Create SoundManager
	SoundManager* snd_mng = new SoundManager();
	snd_mng->load_song(argv[1]); // load song in arguments
	snd_mng->play();
	snd_mng->pause();

	// Create BeatDetector
	BeatDetector* beatdec = new BeatDetector(snd_mng);
	beatdec->audio_process(); // launch beats detection

	LevelGenerator * lvlGen = new LevelGenerator(beatdec, snd_mng, string(argv[1]));

	snd_mng->pause();

	//affichage des beats
	float* beat = beatdec->get_beat();
	int currentPos;
	bool inBeat = false;
	int beatCounter = 0;
	while (true)
	{
		currentPos = snd_mng->get_current_time_PCM() / 1024.f;
		if (beat[currentPos] > 0 && inBeat == false)//on entre dans un beat
		{
			inBeat = true;
			cout << "BEAT ! no"<< beatCounter << endl;
			beatCounter++;
		}
		else if (beat[currentPos] < 1 && inBeat == true)
		{
			inBeat = false;
		}

	}

	/*
	// Create Scene
	Scene Scene(&App, snd_mng, beatdec, argv[1]);
	
	// Set View
	sf::Vector2f Center(0, 0);
	sf::Vector2f HalfSize(400, 300);
	sf::View View(Center, HalfSize);
	App.setView(View);

	bool ctrl_pressed = false; // mémorise l'appui sur Ctrl
	
	while (App.isOpen())
	{
		// Process events
		sf::Event Event;
		while (App.waitEvent(Event))
		{
			
			// Close window : exit
			if (Event.type == sf::Event::Closed) App.close();
			if (Event.type == sf::Event::KeyPressed)
			{
				if (Event.key.code == sf::Keyboard::LControl) ctrl_pressed = true;
				if (ctrl_pressed == true)
				{
					if (Event.key.code == sf::Keyboard::Left) Scene.shift(200000);
					if (Event.key.code == sf::Keyboard::Right) Scene.shift(-200000);
					if (Event.key.code == sf::Keyboard::Down) Scene.extend(860);
					if (Event.key.code == sf::Keyboard::Up) Scene.extend(-860);
					if (Event.key.code == sf::Keyboard::H) snd_mng->change_pitch(0.01f);
					if (Event.key.code == sf::Keyboard::J) snd_mng->change_pitch(-0.01f);
				}
				else
				{
					if (Event.key.code == sf::Keyboard::Left) Scene.shift(10000);
					if (Event.key.code == sf::Keyboard::Right) Scene.shift(-10000);
					if (Event.key.code == sf::Keyboard::Down) Scene.extend(43);
					if (Event.key.code == sf::Keyboard::Up) Scene.extend(-43);
					if (Event.key.code == sf::Keyboard::Add) snd_mng->change_pitch(0.1f);
					if (Event.key.code == sf::Keyboard::Subtract) snd_mng->change_pitch(-0.1f);
				}

				if (Event.key.code == sf::Keyboard::P) snd_mng->pause();
				if (Event.key.code == sf::Keyboard::R) snd_mng->reset();
			}
			if (Event.type == sf::Event::KeyReleased)
			{
				if (Event.key.code == sf::Keyboard::LControl) ctrl_pressed = false;
			}
			if (Event.type == sf::Event::MouseButtonPressed)
			{
				if (Event.mouseButton.button == sf::Mouse::Left) Scene.goto_pos(Event.mouseButton.x);
			}
		}

		// Clear screen
		App.clear(sf::Color(0, 0, 0));

		// Draw Scene
		Scene.draw();

		// Display
		App.display();
	}
	*/
	return EXIT_SUCCESS;
}


