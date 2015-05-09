#include "InGame.h"

#include <iostream>
#include <sstream>
#include <string>
#include <SFML/Graphics.hpp>
using namespace std;
InGame::InGame(unsigned int charSpeed)
{
	personnage = new Character(charSpeed);
	dist.setString("0");
	//dist.setPosition(300, 300);
	dist.setColor(sf::Color::Red);
	dist.setCharacterSize(30);

	
	if (!font.loadFromFile("AmaticB.ttf"))
	{
		// erreur...
	}
	dist.setString("0");
	dist.setFont(font);
	dist.setCharacterSize(50);
	dist.setColor(sf::Color::Black);
	dist.setPosition(50, 580);
}

void InGame::Update(sf::RenderWindow & window)
{
	window.clear();
	personnage->HandleEvent(window);

	personnage->Update(level);

	level.Draw(window);
	personnage->Draw(window);
	if (level.Collision(*personnage))
	{
		cout << "perdu" << endl;
		personnage->Replace();
	}

	//Affichage du score
	std::ostringstream ss;
	ss << personnage->GetPos().x;
	dist.setString(ss.str());
	dist.setPosition(personnage->GetPos().x - 100, 580);
	window.draw(dist);
}

void InGame::Restart()
{

}

InGame::~InGame()
{
	delete personnage;
}
