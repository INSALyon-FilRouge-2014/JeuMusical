#ifndef JUMPSTATE_H
#define JUMPSTATE_H

#include "CharState.h"
class JumpState :
	public CharState
{
public:

	CharState* HandleEvent(sf::Event &);//traite les evenements
	void Update(Character &);//modifie les caracteristiques du personnage
	void Init(int);
	JumpState();
	virtual ~JumpState();

};

#endif