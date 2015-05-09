#ifndef CHARACTER_H
#define CHARACTER_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "CharState.h"
#include "JumpState.h"
#include "RunState.h"
enum CharStates
{ JUMPING,RUNNING, GLIDING };

class Map;

class Character

{
public:
	Character();
	Character(unsigned int speed);
	virtual ~Character(void);
	void HandleEvent(sf::RenderWindow &);
	void Update(Map &);
	void Draw(sf::RenderWindow &);
	void Move(int, int);
	void Replace();
	void SetSprite(sf::Sprite*);
	void SetRunState();
	void SetJumpState(int);
	sf::Vector2f GetPos(){ return pos; };
	void SetPos(float x, float y){ pos.x = x; pos.y = y; };
	sf::FloatRect GetHitbox(){ return actualSprite->getGlobalBounds(); };
	CharState* GetState(){ return actualState; };

protected:
	sf::Sprite *actualSprite;
	sf::Clock updateClock;
	sf::Clock updateClock2;
	CharState* actualState;
	JumpState* jumpState;
	unsigned int v_x;
	RunState* runState;
	sf::Vector2f pos;
};




#endif