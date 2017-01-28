#ifndef FONCTION_H
#define FONCTION_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_FEU 13
#define LG_MAX_LIGNE 100
#define ATTENTE_FIN 3000
#define VITESSE_ROBOT 100000

typedef struct 
	{
	int x,y;
	}COORD;

typedef struct 
	{
	int vie;
	COORD pos;
	COORD pos_old;
	int porteur;
	int ext_x;
	int ext_y;
	COORD memoire;
	int survecu;
	int pas;
	}POMPIER;

typedef struct 
	{
	COORD * Tab;  
	int  * from; //Numéro de toutes les cases testées
	int front,back;
	}QUEUE;

typedef struct 
	{
	COORD tab[MAX_FEU]; //define car il y a au max 13 feux, possibilité de faire une "bonne allocation"
	char intens[MAX_FEU];
	int nbFeu;
	int nbMur;
	}FEU;

#endif
