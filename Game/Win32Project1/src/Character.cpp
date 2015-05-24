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

Character::Character()
{

}

Character::Character(float speed)
{
	runState = new RunState();
	actualState = runState;
	sleep(milliseconds(50));
	jumpState = new JumpState();
	actualState->Update(*this);
	actualSprite->setOrigin((float)SIZE_SPRITE_X / 2, (float)SIZE_SPRITE_Y);
	updateClock.restart();
	pos.x = 0;
	pos.y = SIZE_WINDOW_Y - 128;
	v_x = speed;
	cout << speed << endl;
	if (!buffer.loadFromFile("Bounce.wav"))
	{
		//erreur
	}
	jump.setBuffer(buffer);
	jump.setVolume(50.f);
}

/* A REFAIRE*/
void Character::HandleEvent(Event & event)
{
	CharState * oldState = actualState;
	switch(event.type)
	{
	case Event::KeyPressed:
		if (event.key.code == sf::Keyboard::Space)
		{

			jump.play();
			this->SetJumpState(V_Y);
		}
		break;
	}
}
	


void Character::Update(Map & level, unsigned int temps)
{


	// mise a jour de la texture du sprite toutes les 30ms


	if(updateClock.getElapsedTime()>=Time(milliseconds(20)))
	{
		actualState->Update(*this);
		pos.x = (double)(temps/1000.)*v_x*64.;
		//cout << "deplacement: " << v_x << endl;
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
	if (actualSprite->getPosition().y > (float)SIZE_WINDOW_Y - 128)
	{
		actualSprite->setPosition(pos.x,(float)SIZE_WINDOW_Y - 128);
		
	}
	window.draw(*actualSprite);
}

void Character::Move(double x, double y)
{

	pos.x += x;
	pos.y += y;


}

void Character::Replace()
{
	pos.x = 0;
	pos.y = SIZE_WINDOW_Y - 128;

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
	delete runState;
	delete jumpState;
}
