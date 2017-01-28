#include "main.h"
/*
nom variables à changer
variables non utilisées ds les fct et les tructs
commentaires
indentation
changer all par tab
nom fonctions
*/

int main(int argc, char ** argv)
	{
	char ** tab;
	int Largeur;
	int Hauteur;
	int compteur = 0;
	FEU feu;
	feu.nbFeu = 0;

	POMPIER pompier;
	pompier.vie = 10;
	pompier.survecu = 0;
	pompier.porteur = 0;
	pompier.pas = 0;

	COORD D;

	QUEUE q;

	GRAPHIQUE graph;
	graph.dejaAffiche = 0;

	if(argc!=2)
		{
		printf("Usage: ./a.out fichier.txt.\n");
		return 0;
		}

	calculTaille(argv[1] ,&Largeur ,&Hauteur );	

	tab = Alloc(Largeur, Hauteur);
	tab = remplissage(argv[1], Largeur, Hauteur, tab, &pompier,&feu);
	q.Tab = malloc(Hauteur*Largeur*sizeof(COORD));
	q.from = malloc(Hauteur*Largeur*sizeof(int));
	D.x = pompier.pos.x;
	D.y = pompier.pos.y;
	
	q.front = q.back = 0; // initialisation de la queue
	
	JouerMusique(MUSIQUE);
	initialisation(&graph,Hauteur,Largeur); // Initialisation de la SDL
	Scan(*tab,&q,D,Largeur,Hauteur,'E');
	SetCase(*tab,D,'D',Largeur);	

	RealDraw(*tab, &q, Largeur,Hauteur, &pompier, &feu,&graph);
	SetCase(*tab,D,'D',Largeur);	
	

	if(pompier.survecu == 1)
		{
		RetourFeu(*tab,&pompier,&q,Largeur,Hauteur,&feu,&graph);
		}

	else
		{
		Show(*tab,Largeur,Hauteur,&pompier,&graph);
		COORD tmp;
		tmp.x = 1;
		tmp.y = 1;
		while((tmp.x < Largeur) && (tmp.y < Hauteur))
			{
			tmp.x = tmp.x +1;
			if(tmp.x > Largeur -1)
				{
				tmp.x = 0;
				tmp.y = tmp.y + 2;
				}

			if(GetCase(*tab,tmp,Largeur) != 'x')
				{			
				SetCase(*tab,tmp,'A',Largeur);	
				}
			}
			
		
		while(pompier.survecu==0)
			{
			compteur++;
			q.front = q.back = 0;
			Scan(*tab, &q, pompier.pos, Largeur, Hauteur,'A');
			printf("Le pompier va parcourir tout l'appart\n");
			
			RealDraw(*tab, &q, Largeur,Hauteur, &pompier, &feu,&graph);
			SetCase(*tab,D,'D',Largeur);
			if(pompier.pas >(Largeur)*(Hauteur)-feu.nbMur || compteur >(Largeur)*(Hauteur)-feu.nbMur)
				{
			
				exit(1);
				
				}	
			}
		
		StopFeu(&feu,*tab,Largeur,&pompier,Hauteur);
		}
	Show(*tab,Largeur,Hauteur,&pompier,&graph);

	return 0;
	}
