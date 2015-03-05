#include "Map.h"

//const std::string MAP_TEXTURE = "map.jpg";

const std::string MAP_TEXTURE = "map.jpg";
const int MAP_SIZE = 1280;
using namespace sf;
Map::Map()
{
	if (!mapTexture.loadFromFile(MAP_TEXTURE))
	{
		// error...
	}
	mapSprite1.setTexture(mapTexture);
	mapSprite1.setPosition(0,0);
	mapSprite2.setTexture(mapTexture);
	mapSprite2.setPosition(1280, 0);

}


Map::~Map()
{
}

void Map::Draw(sf::RenderWindow &window)
{
	sf::View currentView = window.getView();
	Vector2f centre = currentView.getCenter();
	float pos = currentView.getCenter().x - currentView.getSize().x / 2;
	if (pos > mapSprite2.getPosition().x )
	{
		mapSprite1 = mapSprite2;
		mapSprite2.setPosition(mapSprite1.getPosition().x + MAP_SIZE,0);
	}

	window.draw(mapSprite1);
	window.draw(mapSprite2);

}