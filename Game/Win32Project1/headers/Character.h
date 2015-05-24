#ifndef CHARACTER_H
#define CHARACTER_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
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
	Character(float speed);
	virtual ~Character(void);
	void HandleEvent(sf::Event &);
	void Update(Map &, unsigned int);
	void Draw(sf::RenderWindow &);
	void Move(double, double);
	void Replace();
	void SetSprite(sf::Sprite*);
	void SetRunState();
	void SetJumpState(int);
	sf::Vector2<double> GetPos(){ return pos; };
	void SetPos(double x, double y){ pos.x = x; pos.y = y; };
	sf::FloatRect GetHitbox(){ return actualSprite->getGlobalBounds(); };
	CharState* GetState(){ return actualState; };

protected:
	sf::Sprite *actualSprite;
	sf::Clock updateClock;
	sf::Clock updateClock2;
	CharState* actualState;
	JumpState* jumpState;
	double v_x;
	RunState* runState;
	sf::Vector2<double> pos;


	/*gestion des sons*/
	sf::SoundBuffer buffer;
	sf::Sound jump;
};




#endif