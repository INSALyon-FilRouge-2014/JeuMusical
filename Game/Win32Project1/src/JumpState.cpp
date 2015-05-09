#include "JumpState.h"
#include "Character.h"
#include <SFML\Graphics.hpp>

static const int GRAV = 3;
static const int V_Y = -40;
const int SIZE_SPRITE_X = 64;
const int SIZE_SPRITE_Y = 96;

using namespace sf;

const std::string CHARACTER_TEXTURE = "jump.png";

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
	v_y = 0;
}

void JumpState::Init(int v_init)
{
	numberOfSprite = 0;
	v_y = v_init;
}

JumpState::~JumpState()
{
	delete stateTexture;
	delete stateSprite;
}

/*inutile*/
CharState* JumpState::HandleEvent(sf::Event & event)
{

	/*
	CharState* returnState = this;
	switch (event.key.code)
	{
	case Keyboard::Space:
		//returnState = new JumpState();
		return returnState;
		break;
	}
	*/
	return this;
}

void JumpState::Update(Character & hero)
{

	v_y += GRAV;
	hero.SetSprite(stateSprite);
	hero.Move(0, v_y);
	
	
}