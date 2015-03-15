#include "Character.h"
#include "CharState.h"
#include "RunState.h"
#include "JumpState.h"
#include "Map.h"
#include <string>

#include <iostream>
using namespace std;
using namespace sf;

const int POS_VIEW = 300;
const int SIZE_SPRITE_X = 64;
const int SIZE_SPRITE_Y = 96;
const int SIZE_WINDOW_Y = 640;
const int SIZE_WINDOW_X = 1024;
static const int V_Y = -25;


Character::Character(void)
{
	runState = new RunState();
	actualState = runState;
	jumpState = new JumpState();
	actualState->Update(*this);
	actualSprite->setOrigin((float)SIZE_SPRITE_X/2,(float)SIZE_SPRITE_Y);
	actualSprite->setPosition((float)SIZE_SPRITE_X/2,(float)SIZE_WINDOW_Y);
	updateClock.restart();
	pos.x = SIZE_WINDOW_X / 2;
	pos.y = SIZE_WINDOW_Y - 128;


}

/* A REFAIRE*/
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
		this->SetJumpState(V_Y);
		break;
	}
	}
	
}


void Character::Update(Map & level)
{


	// mise a jour de la texture du sprite toutes les 0.05s


	if(updateClock.getElapsedTime()>=Time(milliseconds(10)))
	{
		actualState->Update(*this);
		actualSprite->setPosition(pos.x, pos.y);
		updateClock.restart();
	}
	if (pos.y >(SIZE_WINDOW_Y - 128))
	{
		pos.y = SIZE_WINDOW_Y - 128;

		runState->Init();
		actualState = runState;
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


void Character::SetRunState()
{
	if (actualState != runState)
	{
		cout << "setrun" << endl;
		runState->Init();
		actualState = runState;
	}
}

void Character::SetJumpState(int v_init)
{
	if (actualState != jumpState)
	{
		cout << "setjump "<< v_init << endl;
		jumpState->Init(v_init);
		actualState = jumpState;
	}

}



Character::~Character(void)
{
	delete actualState;
}
