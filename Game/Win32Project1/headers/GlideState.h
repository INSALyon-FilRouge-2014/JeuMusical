#ifndef GLIDESTATE_H
#define GLIDESTATE_H

#include "CharState.h"
class GlideState :
	public CharState
{
public:

	CharState* HandleEvent(sf::Event &);//traite les evenements
	void Update(Character &);//modifie les caracteristiques du personnage


	GlideState();
	virtual ~GlideState();
};

#endif