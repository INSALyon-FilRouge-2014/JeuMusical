#ifndef RUNSTATE_H

#define RUNSTATE_H

#include "CharState.h"

class RunState :
	public CharState
{
public:


	CharState* HandleEvent(sf::Event &);//traite les evenements
	void Update(Character &);//modifie les caracteristiques du personnage
	void Init();
	RunState();
	virtual ~RunState();
};

#endif