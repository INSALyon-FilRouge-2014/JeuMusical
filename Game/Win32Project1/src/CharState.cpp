#include "CharState.h"
#include "Character.h"
#include <SFML\Graphics.hpp>

CharState::CharState()
{
}


CharState::~CharState()
{
}

CharState* CharState::HandleEvent(sf::Event & e)
{
	return this;
}

void CharState::Update(Character & c)
{


}