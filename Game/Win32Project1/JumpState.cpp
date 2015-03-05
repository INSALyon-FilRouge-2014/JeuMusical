#include "JumpState.h"
#include "Character.h"
#include <SFML\Graphics.hpp>

static const int GRAV = 5;
static const int MOVE_SPEED = 60;
static const int V_Y = -40;
const int SIZE_SPRITE_X = 180;
const int SIZE_SPRITE_Y = 248;

using namespace sf;

const std::string CHARACTER_TEXTURE = "ss1.png";

JumpState::JumpState()
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
	v_y = V_Y;
	v_x = MOVE_SPEED;
}

void JumpState::Init()
{
	numberOfSprite = 0;
	v_y = V_Y;
}

JumpState::~JumpState()
{
	delete stateTexture;
	delete stateSprite;
}

CharState* JumpState::HandleEvent(sf::Event & event)
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

void JumpState::Update(Character & hero)
{
	
	stateSprite->setTextureRect(IntRect((numberOfSprite % 5)*SIZE_SPRITE_X, ((int)numberOfSprite / 5)*SIZE_SPRITE_Y, SIZE_SPRITE_X, SIZE_SPRITE_Y));
	numberOfSprite = (numberOfSprite + 1) % 10;
	updateClock.restart();
	hero.SetSprite(stateSprite);
	hero.Move(v_x, v_y);
	v_y += GRAV;
	
}