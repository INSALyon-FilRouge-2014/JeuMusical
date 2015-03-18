#include "Character.h"
#include "RunState.h"
#include <SFML/Graphics.hpp>
#include <string>
#include "JumpState.h"
using namespace sf;

static const int MOVE_SPEED = 13;
const int SIZE_SPRITE_X = 64;
const int SIZE_SPRITE_Y = 96;
const std::string CHARACTER_TEXTURE = "Sprite2.png";

RunState::RunState()
{
	numberOfSprite = 0;
	stateTexture = new Texture();
	if (!stateTexture->loadFromFile(CHARACTER_TEXTURE))
	{
		// error...
	}

	stateSprite = new Sprite();
	stateSprite->setTexture(*stateTexture);

	stateSprite->setOrigin((float)SIZE_SPRITE_X / 2, (float)SIZE_SPRITE_Y);
	v_x = MOVE_SPEED;
	v_y = 0;

}


RunState::~RunState()
{
	delete stateSprite;
	delete stateTexture;
}

void RunState::Init()
{
	numberOfSprite = 0;
	v_y = 0;
}
CharState* RunState::HandleEvent(Event & event)//traite les evenements
{
	CharState* returnState = this;
	switch (event.key.code)
	{
	case Keyboard::Space:
		returnState = new JumpState();
		return returnState;
		break;
	}

	return this;
}
void RunState::Update(Character & hero)//modifie les caracteristiques du personnage
{
	if (updateClock.getElapsedTime() >= Time(milliseconds(50)))
	{
		stateSprite->setTextureRect(IntRect((numberOfSprite % 6)*SIZE_SPRITE_X, 0, SIZE_SPRITE_X, SIZE_SPRITE_Y));
		numberOfSprite = (numberOfSprite + 1) % 6;
		hero.SetSprite(stateSprite);
		updateClock.restart();
	}
	hero.Move(MOVE_SPEED,0);

}



