#include "fonction.h"
#include "fonction_sdl.h"

//Fonctions de fonction.h

void calculTaille(char * fichier, int * Largeur, int * Hauteur);
char ** Alloc(int Largeur, int Hauteur);
char ** remplissage(char * fichier, int Largeur, int Hauteur ,char ** tab, POMPIER * pompier, FEU * feu);
void PushBack(QUEUE* q, COORD c);
COORD PopFront(QUEUE* q);
int Empty(QUEUE* q);
void SetCase(char * tab, COORD c, char toreplace, int largeur);
char GetCase(char * tab, COORD c, int largeur);
void Show(char * tab, int largeur, int hauteur, POMPIER * pompier, GRAPHIQUE * graph);
int Scan(char * tab, QUEUE* q, COORD D, int largeur, int hauteur, char carac);
int RealDraw(char * tab, QUEUE * q, int largeur, int hauteur, POMPIER * pompier, FEU * feu,  GRAPHIQUE * graph);
void RetourFeu(char * tab, POMPIER * pompier, QUEUE * q, int largeur, int hauteur, FEU * feu, GRAPHIQUE * graph);
void StopFeu(FEU * feu, char * tab, int largeur, POMPIER * pompier, int hauteur);
void efface(char * tab, char carac, int hauteur, int largeur);
void AfficheTerm(int hauteur, int largeur, char * tab, POMPIER * pompier);

//Fonctions de fonction_sdl.h

int initialisation(GRAPHIQUE * graph, int hauteur, int largeur);
void AfficheSDL(GRAPHIQUE * graph, COORD pos, SDL_Rect * rect_pos, char carac, char carac_old, SDL_Rect * rect_pos_old);
void AfficheTout(int hauteur, int largeur, GRAPHIQUE * graph, char * tab, POMPIER * pompier);
void AfficheTexte(POMPIER * pompier, GRAPHIQUE * graph, int hauteur, int largeur);
void JouerMusique(char * NomMusique);
