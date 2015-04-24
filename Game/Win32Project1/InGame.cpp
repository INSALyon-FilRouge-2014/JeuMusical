#include "InGame.h"

#include <iostream>

using namespace std;
InGame::InGame(unsigned int charSpeed)
{
	personnage = new Character(charSpeed);
}

void InGame::Update(sf::RenderWindow & window)
{
	personnage->HandleEvent(window);

	personnage->Update(level);
	window.clear();
	level.Draw(window);
	personnage->Draw(window);
	if (level.Collision(*personnage))
	{
		cout << "perdu" << endl;
		personnage->Replace();
	}
}

void InGame::Restart()
{

}

InGame::~InGame()
{
	delete personnage;
}
