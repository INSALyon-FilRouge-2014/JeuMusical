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
	sf::Vector2f GetPos(){ return pos; };
	sf::FloatRect GetHitbox(){ return actualSprite->getGlobalBounds(); };

protected:
	sf::Sprite *actualSprite;
	sf::Clock updateClock;
	sf::Clock updateClock2;
	CharState* actualState;
	JumpState* jumpState;

	RunState* runState;
	sf::Vector2f pos;
};




#endif