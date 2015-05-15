#ifndef INGAME_H
#define INGAME_H
#include "GameState.h"
#include "Character.h"
#include "Map.h"
class InGame :
	public GameState
{
public:
	InGame(float charSpeed);
	void Update(sf::RenderWindow &);
	void Restart();
	void HandleEvent(sf::RenderWindow &window);
	virtual ~InGame();

protected:
	Character* personnage;
	Map level;
	sf::Text dist;
	sf::Clock clock;
	sf::Text time;
	sf::Font font;
};

#endif