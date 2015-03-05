#ifndef CHARACTER_H
#define CHARACTER_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "CharState.h"
#include "JumpState.h"
#include "RunState.h"
enum CharStates
{ JUMPING,RUNNING, GLIDING };


class Character

{
public:
	Character(void);
	virtual ~Character(void);
	void HandleEvent(sf::RenderWindow &);
	void Update(void);
	void Draw(sf::RenderWindow &);
	void Move(int, int);
	void SetSprite(sf::Sprite*);


protected:
	sf::Sprite *actualSprite;
	sf::Vector2i hitbox;
	sf::Clock updateClock;
	sf::Clock updateClock2;
	CharState* actualState;
	JumpState* jumpState;

	RunState* runState;
	float posx;
	float posy;
};




#endif