#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <cstdio>
#include <iostream>
#include <sstream>

class Obstacle
{

public:
	static const int H_SOL = 9;// la hauteur a laquelle sont positionnés les blocs de sol
	static const int H_PLAFOND = 1;//le plus haut bloc qu'on puisse poser
	static const int H_PERSO = 2;

	enum TypeObstacle { CAISSE, NUAGE, PIC };

	unsigned int getPosition(){ return position; }

	unsigned int getMSPosition(){ return MSPosition; }

	unsigned int getPCMPosition(){ return PCMPosition; }

	unsigned int getPCM1024Position(){ return  (unsigned int)(PCMPosition / 1024.f); }

	int getHauteur(){ return hauteur; }

	void setHauteur(int h){ hauteur = h; }

	void setPositions(unsigned int pos, unsigned int pcmpos, int mspos) {position = pos; PCMPosition = pcmpos; MSPosition = mspos;}

	TypeObstacle getType(){ return type; }

	void display(){printf("Obstacle : hauteur = %d ; type = %d", hauteur , type); }

	Obstacle(unsigned int pos, unsigned int pcmpos, int mspos ,int h, TypeObstacle typ)
		:position(pos), MSPosition(mspos), PCMPosition(pcmpos), hauteur(h), type(typ){}

	Obstacle(int h, TypeObstacle typ)
		:position(0), MSPosition(0), PCMPosition(0), hauteur(h), type(typ){}

	virtual ~Obstacle(){}


private:
	unsigned int position;//position en X

	unsigned int MSPosition;//position de l'obstacle en ms

	unsigned int PCMPosition;//position de l'obstacle en PCM de la musique
	//NB : PCM / 1024 regrouppement des echantillons par 1024

	int hauteur;//position en Y

	TypeObstacle type;

};

#endif
