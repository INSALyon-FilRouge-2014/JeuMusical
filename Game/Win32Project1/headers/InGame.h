#ifndef INGAME_H
#define INGAME_H
#include <string>
#include "GameState.h"
#include "Character.h"
#include "Map.h"
#include "SoundManager.h"
#include "XMLReader.h"
class InGame :
	public GameState
{
public:
	InGame(float charSpeed, std::string name);
	void Update(sf::RenderWindow &);
	void Restart();
	void HandleEvent(sf::RenderWindow &window);
	virtual ~InGame();

protected:
	Character* personnage;
	Map* level;
	sf::Text dist;
	sf::Clock clock;
	sf::Text time;
	sf::Font font;
	sf::Text titre;
	SoundManager sm;
	LevelInfo info;

};

#endif