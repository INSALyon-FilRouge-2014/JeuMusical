#ifndef OBSTACLE_H
#define OBSTACLE_H

class Obstacle
{

public:
	enum TypeObstacle { CAISSE, NUAGE, PIC };

	unsigned int getPosition(){ return position; }

	unsigned int getPCMPosition(){ return PCMPosition; }

	unsigned int getPCM1024Position(){ return unsigned int(PCMPosition / 1024.f); }

	int getHauteur(){ return hauteur; }

	TypeObstacle getType(){ return type; }

	Obstacle(unsigned int pos, unsigned int pcmpos, int h, TypeObstacle typ)
		:position(pos), PCMPosition(pcmpos), hauteur(h), type(typ){}

	virtual ~Obstacle(){}

private:
	unsigned int position;//position en X

	unsigned int PCMPosition;//position de l'obstacle en PCM de la musique
	//NB : PCM / 1024 regrouppement des echantillons par 1024

	int hauteur;//position en Y

	TypeObstacle type;

};

#endif