#ifndef OBSTACLE_H
#define OBSTACLE_H

class Obstacle
{

public:
	enum TypeObstacle { CAISSE, NUAGE, PIC };

	int getPosition(){ return position; }

	int getHauteur(){ return hauteur; }

	int getType(){ return type; }

	Obstacle(int pos, int h, TypeObstacle typ)
		:position(pos), hauteur(h), type(typ){}

private:
	int position;//position en X

	int hauteur;//position en Y

	TypeObstacle type;

};

#endif