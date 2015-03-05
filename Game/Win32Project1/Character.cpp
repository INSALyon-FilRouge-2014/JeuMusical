#include "Character.h"
#include "CharState.h"
#include "RunState.h"
#include "JumpState.h"
#include <string>

#include <iostream>
using namespace std;
using namespace sf;

const int POS_VIEW = 300;
const int SIZE_SPRITE_X = 180;
const int SIZE_SPRITE_Y = 248;
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
	posx = SIZE_SPRITE_X / 2;
	posy = SIZE_WINDOW_Y - 60;

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
			jumpState->Init();
			actualState = jumpState;
		}
		break;
	}
	}
	
}


void Character::Update()
{


	// mise a jour de la texture du sprite toutes les 0.05s
	if(updateClock.getElapsedTime()>=Time(milliseconds(50)))
	{
		actualState->Update(*this);
		actualSprite->setPosition(posx, posy);
		updateClock.restart();
	}
	if (posy >SIZE_WINDOW_Y - 60)
	{
		posy = SIZE_WINDOW_Y - 60;
		runState->Init();
		actualState = runState;
	}
}


void Character::Draw(RenderWindow & window)
{

	sf::View currentView = window.getView();
	currentView.setCenter(posx + POS_VIEW,SIZE_WINDOW_Y/2);
	window.setView(currentView);
	window.draw(*actualSprite);

}

void Character::Move(int x, int y)
{
	posx += x;
	posy += y;
	

}

void Character::SetSprite(Sprite* sprite)
{
	actualSprite = sprite;

}

Character::~Character(void)
{
	delete actualState;
}
