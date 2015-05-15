#ifndef PLATFORM_H

#define PLATFORM_H

#include <SFML/Graphics.hpp>
class Platform
{
public:
	enum TypeObstacle { CAISSE, NUAGE, PIC };
	Platform(sf::Texture*, float,float, TypeObstacle);
	Platform(float, float, TypeObstacle);
	virtual ~Platform();
	void SetTexture(sf::Texture* texture);
	sf::Vector2f GetPos(){ return pos; };
	sf::FloatRect GetHitBox(){ return sprite.getGlobalBounds(); };
	int GetType(){ return type; };
	void Draw(sf::RenderWindow & window);

protected:
	sf::Sprite sprite;
	sf::Vector2f pos;
	sf::FloatRect hitbox;
	TypeObstacle type;
};

#endif