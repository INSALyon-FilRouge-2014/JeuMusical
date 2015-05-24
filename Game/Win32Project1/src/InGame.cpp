#include "InGame.h"

#include <iostream>
#include <sstream>
#include <string>
#include <SFML/Graphics.hpp>
#include "SoundManager.h"
#include "XMLReader.h"
using namespace std;
using namespace sf;
InGame::InGame(float charSpeed, string name)
{
	XMLReader* reader = new XMLReader(name+".xml");
	info = reader->readInfo();
	personnage = new Character(info.vitesse);
	delete reader;
	dist.setString("0");
	//dist.setPosition(300, 300);
	dist.setColor(sf::Color::Red);
	dist.setCharacterSize(30);
	cout << "creation du niveau" << endl;
	level = new Map(name+".xml");
	if (!font.loadFromFile("AmaticB.ttf"))
	{
		// erreur...
	}
	dist.setString("0");
	dist.setFont(font);
	dist.setCharacterSize(30);
	dist.setColor(sf::Color::Black);
	dist.setPosition(50, 600);


	time.setString("0");
	time.setFont(font);
	time.setCharacterSize(30);
	time.setColor(sf::Color::Black);
	time.setPosition(50, 590);

	titre.setString(name);
	titre.setFont(font);
	time.setCharacterSize(30);
	time.setColor(sf::Color::Black);
	time.setPosition(50, 590);

	sm.load_song((char*)string(name+".mp3").c_str());
	sm.play();


	clock.restart();
}

void InGame::Update(sf::RenderWindow & window)
{
	window.clear();
	HandleEvent(window);

	
	personnage->Update(*level, sm.get_current_time_MS());
	cout << sm.get_current_time_MS() << endl;
	level->Draw(window);
	personnage->Draw(window);
	if (level->Collision(*personnage))
	{
		cout << "perdu" << endl;
		Restart();

	}

	//Affichage du score
	std::ostringstream ss;
	ss << personnage->GetPos().x;
	dist.setString("dist: " + ss.str());
	dist.setPosition(personnage->GetPos().x - 150, 590);
	window.draw(dist);

	std::ostringstream s;
	s << (int)clock.getElapsedTime().asSeconds();
	/*if ((int)clock.getElapsedTime().asSeconds() == 10)
	{
		cout << personnage->GetPos().x << endl;
	}*/
	time.setString("time: " + s.str());
	time.setPosition(personnage->GetPos().x - 150, 560);
	window.draw(time);
}

void InGame::Restart()
{
	sm.reset();
	clock.restart();
	personnage->Replace();
	level->Reset();
}


void InGame::HandleEvent(sf::RenderWindow &window)
{
	Event event;
	while (window.pollEvent(event))
	{
		switch (event.type)
		{
		case Event::Closed:
			window.close();
			break;
		case Event::KeyPressed:
			if (event.key.code == sf::Keyboard::Space)
			{
				personnage->HandleEvent(event);
			}
			else if (event.key.code == sf::Keyboard::R)
			{
				Restart();
			}
			break;
		}
	}

}

InGame::~InGame()
{
	delete personnage;
}
