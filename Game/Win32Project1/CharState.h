#ifndef CHARSTATE_H
#define CHARSTATE_H


#include <SFML/Graphics.hpp>
class Character;


class CharState
{
protected:

	int v_x;
	int v_y;
	sf::Texture *stateTexture;
	sf::Sprite *stateSprite;
	int numberOfSprite;
	sf::Clock updateClock;

public:
	CharState();
	virtual CharState* HandleEvent(sf::Event &) ;//traite les evenements
	virtual void Update(Character & ) ;//modifie les caracteristiques du personnage
	virtual ~CharState();
	bool AscOrDesc(){ return v_y >= 0; };

private:




};

#endif