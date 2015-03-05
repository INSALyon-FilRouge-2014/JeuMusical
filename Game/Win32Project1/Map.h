#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>

class Map
{
public:
	Map();
	virtual ~Map();
	void Draw(sf::RenderWindow &window);

protected:
	sf::Sprite mapSprite1;
	sf::Sprite mapSprite2;
	sf::Texture mapTexture;



};

#endif