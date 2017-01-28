#ifndef FCT_SDL_H
#define FCT_SDL_H

#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>


#define TAILLE_CASE 15
#define MUSIQUE "musique.mp3"

typedef struct 
	{
	SDL_Surface * chemin;
	SDL_Surface * mur;
	SDL_Surface * pacmanOuvert;
	SDL_Surface * pacmanFerme;
	SDL_Surface * feu;
	SDL_Surface * extincteur;
	SDL_Surface * ecran;
	SDL_Surface * mort;
	SDL_Surface * feu2;	
	SDL_Surface * texte;
	int act; //intact variable pour ouvrir et fermer la bouche du pacman
	int dejaAffiche;
	}GRAPHIQUE;

#endif
