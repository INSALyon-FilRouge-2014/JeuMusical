#ifndef GameState_H
#define GameState_H
#include <SFML/Graphics.hpp>
class GameState
{
public:
	GameState();
	virtual void Update(sf::RenderWindow window){};
	virtual void Restart(){};
	virtual ~GameState();
};

#endif