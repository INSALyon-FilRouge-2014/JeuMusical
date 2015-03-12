#include "Character.h"
#include "CharState.h"
#include "RunState.h"
#include "JumpState.h"
#include <string>

#include <iostream>
using namespace std;
using namespace sf;

const int POS_VIEW = 300;
const int SIZE_SPRITE_X = 64;
const int SIZE_SPRITE_Y = 96;
const int SIZE_WINDOW_Y = 640;
const int SIZE_WINDOW_X = 1024;


Character::Character(void)
{
	runState = new RunState();
	actualState = runState;
	jumpState = new JumpState();
	actualState->Update(*this);
	actualSprite->setOrigin((float)SIZE_SPRITE_X/2,(float)SIZE_SPRITE_Y);
	actualSprite->setPosition((float)SIZE_SPRITE_X/2,(float)SIZE_WINDOW_Y);
	updateClock.restart();
	pos.x = SIZE_SPRITE_X / 2;
	pos.y = SIZE_WINDOW_Y - 64;


}

/* A REFAIRE: HANDLEEVENT DES STATES SANS ALLOCATION DYNAMIQUE*/
void Character::HandleEvent(RenderWindow &window)
{
	Event event;
	CharState * oldState = actualState;
	while(window.pollEvent(event))
	{
	switch(event.type)
	{
	case Event::Closed:
        window.close();
        break;
	case Event::KeyPressed:
		if (actualState != jumpState)
		{
			jumpState->Init(-30);
			actualState = jumpState;
		}
		break;
	}
	}
	
}


void Character::Update()
{


	// mise a jour de la texture du sprite toutes les 0.05s

	if (pos.y >(SIZE_WINDOW_Y - 64))
	{
		pos.y = SIZE_WINDOW_Y - 64;
		
		runState->Init();
		actualState = runState;
	}
	if(updateClock.getElapsedTime()>=Time(milliseconds(20)))
	{
		actualState->Update(*this);
		actualSprite->setPosition(pos.x, pos.y);
		updateClock.restart();
	}

}


void Character::Draw(RenderWindow & window)
{

	sf::View currentView = window.getView();
	currentView.setCenter(pos.x + POS_VIEW,SIZE_WINDOW_Y/2);
	window.setView(currentView);
	window.draw(*actualSprite);
}

void Character::Move(int x, int y)
{

	pos.x += x;
	pos.y += y;


}

void Character::SetSprite(Sprite* sprite)
{
	actualSprite = sprite;
	actualSprite->setPosition(pos.x, pos.y);

}

Character::~Character(void)
{
	delete actualState;
}
