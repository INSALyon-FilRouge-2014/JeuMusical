#ifndef INGAME_H
#define INGAME_H
#include "GameState.h"
#include "Character.h"
#include "Map.h"
class InGame :
	public GameState
{
public:
	InGame(unsigned int charSpeed);
	void Update(sf::RenderWindow &);
	void Restart();
	virtual ~InGame();

protected:
	Character* personnage;
	Map level;
};

#endif