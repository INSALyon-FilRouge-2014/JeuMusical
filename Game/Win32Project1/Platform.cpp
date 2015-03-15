#include "Platform.h"

#include <SFML/Graphics.hpp>
using namespace sf;


static const int SIZE_PLAT = 64;

Platform::Platform(Texture* texture, float x, float y)
{
	sprite.setTexture(*texture);

	sprite.setOrigin((float)SIZE_PLAT / 2, (float)SIZE_PLAT);
	pos.x = x * SIZE_PLAT;
	pos.y = y * SIZE_PLAT;
	sprite.setPosition(pos.x, pos.y);
	hitbox = sprite.getGlobalBounds();
}


Platform::~Platform()
{
}



void Platform::Draw(sf::RenderWindow & window)
{ 
	window.draw(sprite); 
}