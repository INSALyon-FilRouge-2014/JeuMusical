#ifndef PLATFORM_H

#define PLATFORM_H

#include <SFML/Graphics.hpp>
class Platform
{
public:
	Platform(sf::Texture*, float,float);
	virtual ~Platform();
	sf::Vector2f GetPos(){ return pos; };
	sf::FloatRect GetHitBox(){ return sprite.getGlobalBounds(); };
	void Draw(sf::RenderWindow & window);

protected:
	sf::Sprite sprite;
	sf::Vector2f pos;
	sf::FloatRect hitbox;

};

#endif