#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Platform.h"
#include "Character.h"

class Map
{
public:
	Map();
	virtual ~Map();
	void Draw(sf::RenderWindow &window);
	bool Collision(Character&);

protected:
	sf::Sprite mapSprite1;
	sf::Sprite mapSprite2;
	sf::Texture mapTexture;

	sf::Texture platTexture;
	std::vector<Platform>* platformtab;


};

#endif