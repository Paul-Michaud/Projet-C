#include "main.h"

/*************************************************************************/
/*			    Fonction calculTaille 			 */					
/*  Input :    La fichier appart.txt La largeur en E/S La sortie en E/S  */
/*  Objectif : Modifier les variables largeur et hauteur pour qu'elles   */
/*	       correspondent aux dimensions de l'appart du fichier.txt   */
/*************************************************************************/

void calculTaille(char * fichier, int * Largeur, int * Hauteur)
	{
	FILE * fp = NULL;
	int i = 0;
	char chaine[LG_MAX_LIGNE];
	char * chaine2;
	
	fp = fopen(fichier,"r");

	if(fp==NULL)
		{
		printf("Erreur d'ouverture");
		exit(1);
		}
	
	fgets(chaine, LG_MAX_LIGNE, fp);

	for(i=0;i<strlen(chaine);i++)
		{
		if(chaine[i]==':')
			{
			chaine[i]='\0';
			chaine2=&chaine[i+1];
			chaine2[strlen(chaine2+1)]='\0';
			}
		}
	fclose(fp);
	
	*Largeur = atoi(chaine);  /* On convertit chaine et chaine 2 */
	*Hauteur = atoi(chaine2); /*   en int car ils sont en char   */
	}


/*************************************************************************/
/*			    Fonction tabocation				 */					
/*  Input :     La Largeur et la Hauteur de l'appart  			 */
/*  Objectif :  tabocation dynamique (en fonction de la largeur et la    */
/*		hauteur) d'un tableau à 2 dimensions de char  		 */
/*  Output :    L'adresse de début du tableau taboué                     */	         
/*************************************************************************/

char ** Alloc(int Largeur, int Hauteur)
	{
	int i;

	char **tab = (char **)malloc(sizeof(char*)*Hauteur);
	char *tab2 = (char *)malloc(sizeof(char)*Largeur*Hauteur);
	for(i = 0 ; i < Hauteur ; i++)
		{
		tab[i] = &tab2[i*Largeur];
		}
	return tab;
	}


/*************************************************************************/
/*			    Fonction SetCase				 */					
/*  Input :     Le tableau à 2 dim la coordonnée de l'endroit que l'on   */
/*		veut modifier le char qu'on mettra à la place de l'ancien*/
/*  Objectif :  Remplacer le char qui se trouve à la coord par un autre  */
/*		(par celui envoyé en 3ieme paramètre) 			 */	         
/*************************************************************************/
void SetCase(char * tab, COORD c, char toreplace, int largeur)
	{
	tab[c.y*largeur+c.x] = toreplace;
	}
 

/*************************************************************************/
/*			    Fonction GetCase				 */					
/*  Input :     Le tableau à 2 dim la coordonnée de l'endroit duquel on  */
/*		veut connaitre le char					 */
/*  Objectif :  Renvoyer le caractère qui se trouve à la position        */
/*		envoyée à la fonction	                                 */
/*  Output :    Le char en question 					 */	         
/*************************************************************************/

char GetCase(char * tab, COORD c, int largeur)
	{
	return tab[c.y*largeur+c.x];
	}


/*************************************************************************/
/*			    Fonction remplissage			 */					
/*  Input :     Le fichier.txt de l'appart, la Largeur et la Hauteur du  */
/*		Le tableau à 2 dimensions, le pompier (robot) et une     */
/*	 	variable de type feu		  			 */
/*  Objectif :  Remplir le tableau à 2 dim avec la carte		 */
/*		Mettre la position de départ du pompier au niveau du 'D' */
/*		Sauvegarder la position de l'extincteur			 */
/*		Sauvegarder la position des feux (juste pour pouvoir les */
/*		réafficher si ils disparaissent) 			 */
/*		Vérifier qu'il y à un D et un E				 */
/*  Output :    L'adresse de début du tableau à 2 dimensions             */	         
/*************************************************************************/

char ** remplissage(char * fichier, int Largeur, int Hauteur, char ** tab, POMPIER * pompier, FEU * feu)
	{
	char chaine[Largeur];
	FILE * fp = NULL;
	int i = 0;
	int j = 0;
	int k = 0;
	int depOk = 0; // Variable pour vérifier si le départ existe
	int extOk = 0; // Variable pour vérifier si l'extincteur existe

	fp = fopen(fichier,"r");

	if(fp==NULL)
		{
		printf("Erreur d'ouverture");
		exit(1);
		}

	fgets(chaine, Largeur, fp); // Suppression de la première ligne
	
	for(i=0;i<Hauteur;i++)
		{
		for(j=0;j<Largeur+1;j++)
			{
			if ( j < Largeur )
				{
				tab[i][j]=fgetc(fp);
				
				if(tab[i][j]=='D')
					{
					pompier->pos.x=j;
					pompier->pos.y=i;
					depOk = 1;
					}

				if(tab[i][j]=='E')
					{
					pompier->ext_x=j;
					pompier->ext_y=i;
					extOk = 1;
					}
				if(tab[i][j]=='x')
					{
					feu->nbMur++;
					}

				if(tab[i][j]=='1' || tab[i][j]=='2' || tab[i][j]=='3')	
					{
					feu->tab[k].x = j;
					feu->tab[k].y = i; 
					feu->nbFeu++;
					feu->intens[k] = GetCase(*tab,feu->tab[k],Largeur);
					k++;
					}
				}
			else
				{
				fgetc(fp);
				}
			}
		}

	fclose(fp);

	if(depOk != 1)
		{
		printf("Départ non trouvé, veuillez revoir votre plan.\n");
		exit(1);
		}

	if(extOk != 1)
		{
		printf("Extincteur non trouvé, veuillez revoir votre plan.\n");
		exit(1);
		}
	return tab;
	}


/*************************************************************************/
/*			    Fonction PushBack				 */					
/*  Input :     La queue et la coordonnée où le robot se trouve		 */
/*  Objectif :  Initialiser le tableau des positions que le robot        */
/*		parcourera avec la position du départ 			 */	         
/*************************************************************************/

void PushBack(QUEUE * q, COORD c)
	{
	q->Tab[q->back++] = c;
	}


/*************************************************************************/
/*			    Fonction PopFront				 */					
/*  Input :     La queue 						 */
/*  Objectif :  Renvoyer la dernière coordonnée scannée pour pouvoir     */
/*		continuer à scanner les alentours			 */
/*  Output :    La coordonnée en question			         */	         
/*************************************************************************/

COORD PopFront(QUEUE * q)
	{
	return q->Tab[q->front++];
	}


/*************************************************************************/
/*			    Fonction Show				 */					
/*  Input :     Le tableau à 2 dim, largeur/hauteur, le robot de type    */
/*		POMPIER et le grah de type GRAPHIQUE			 */
/*  Objectif :  Afficher le tableau dans le terminal et en SDL 	         */	         
/*************************************************************************/

void Show(char * tab, int largeur, int hauteur, POMPIER * pompier, GRAPHIQUE * graph)
	{
	int i,j;
	AfficheTerm(hauteur,largeur,tab,pompier);

	SDL_Flip(graph->ecran);
	SDL_Rect rect_pos;
	SDL_Rect rect_pos_old;

	for(j=0;j<hauteur;j++)
		{
 		for(i=0;i<largeur;i++)
			{
			COORD tmp;
			tmp.x = i;
			tmp.y = j;
			rect_pos.x = TAILLE_CASE*i;
			rect_pos.y = TAILLE_CASE*j;
			rect_pos_old.x = TAILLE_CASE*pompier->pos_old.x;
			rect_pos_old.y = TAILLE_CASE*pompier->pos_old.y;
			AfficheSDL(graph,tmp,&rect_pos,GetCase(tab,tmp,largeur),GetCase(tab,pompier->pos_old,largeur),&rect_pos_old);
			}
		}
		AfficheTexte(pompier,graph,hauteur,largeur); 
		SDL_Flip(graph->ecran);
	}
 
/*************************************************************************/
/*			    Fonction Scan				 */
/*			Trouvée sur internet et adaptée			 */					
/*  Input :     Le tableau, la queue, la coord du départ, hauteur/largeur*/
/*		Le caractère à trouver					 */
/*  Objectif :  Scanner la map (=le tab à 2 dim) et s'arrêter quand 	 */
/*		on à trouver le caractère 				 */
/*		Modifier le champ Tab de la queue avec les positions du  */
/*		départ au caractère.					 */
/*		Le seul inconvénient est que les positions vont de 	 */
/*		l'arrivée au départ il faut donc les inverser après      */			
/*  Output :    1 ou 0						         */	         
/*************************************************************************/
	
int Scan(char * tab, QUEUE * q, COORD D, int largeur, int hauteur, char carac )
	{
	PushBack(q,D);
	SetCase(tab,D,'.',largeur); 
	// Dans cette fonction on met un '.' sur toutes les positions déjà scannées pour ne pas y repasser
	while(!((q->back)<=(q->front))) // Tant qu'on n'est pas à la fin du tab
		{
		int vec[4][2] = {{1,0},{-1,0},{0,1},{0,-1}}; // Tableau avec des vecteurs pour "bouger" en bas/en haut/à droite/à gauche
		int i;
		int from = q->front;
		COORD current = PopFront(q);
		for(i=0;i<4;i++)
			{
			COORD candidate; // Position que l'on scanne
			candidate.x = current.x + vec[i][0]; // On fait bouegr cette position suivant les vecteurs vu ci-dessus
			candidate.y = current.y + vec[i][1];
			if ((GetCase(tab,candidate,largeur) == ' ') || (GetCase(tab,candidate,largeur) == carac) || GetCase(tab,candidate,largeur) == '1' || GetCase(tab,candidate,largeur) == 'D') //Toutes les cases où l'on peut se déplacer
				{
 				q->from[q->back] = from;
				PushBack(q,candidate);
				
				if(GetCase(tab,candidate,largeur) == carac) // Si on trouve le caractère de fin on éfface tout les points et on sor de la fonction
					{
					efface(tab,'.',hauteur,largeur);
					return 1;			
					}
				SetCase(tab,candidate,'.',largeur); // Sinon on met un '.' et on continue
				}
			}
		}
	
	return 0; // Caractère non trouvé
	}


/*************************************************************************/
/*			    Fonction RealDraw				 */					
/*  Input :     Le tableau, la queue, hauteur/largeur, le pompier	 */
/*		Les coordonnées des feux et la struct de type GRAPHIQUE	 */
/*  Objectif :  Remettre le tableau des positions dans le bon ordre      */
/*		(j'aurais surement du faire une fonction pour ça)	 */
/*		Changer la positions du robot pompier en fonction de     */
/*		celles acquéris grâce à la fonction scan		 */			
/*  Output :    1 ou 0						         */	         
/*************************************************************************/

int RealDraw(char * tab, QUEUE * q, int largeur, int hauteur, POMPIER * pompier, FEU * feu,  GRAPHIQUE * graph)
	{
	int curs = q->back-1;
	int i = 0;
	int j = 0;
	int k = 0;	
	
	while(curs!=0) //On compte le nombre d'élement dans le tableau from = le nombre de pas max
		{
		curs = q->from[curs];
		i++;
		}
	
	
	int bonOrdre[i]; //On crée un tableau où l'on mettra les positions des pas dans le bon ordre
	
	curs = q->back-1; //On remet curse à fin

	int temp = 1; //On commence à 1 sinon on supprime la case de départ

	//On remet dans un tableau dans le bon ordre en commençant par la fin car on connait la taille du tableau (calculé ci-dessus)
	while(i!=0) // i est au max du tableau donc on commence par la et on descend
		{
		bonOrdre[i] = curs;
		curs = q->from[curs];
		i--;
		}

	i = 1; // On commence à 1 sinon on supprime la case de départ
	
	while(bonOrdre[i-1] != q->back-1)
		{
		curs = bonOrdre[i];
		i++;
		
		pompier->pos_old.x = pompier->pos.x;
		pompier->pos_old.y = pompier->pos.y;
		pompier->pos.x = q->Tab[curs].x;  
		pompier->pos.y = q->Tab[curs].y;
		pompier->pas = pompier->pas + 1;
		SetCase(tab,q->Tab[temp],' ',largeur); // On supprime la trace du robot
		
		
		for(j=0;j<feu->nbFeu;j++) //On réaffiche les foyers tout le temps car quand le robot passe dessus ils s'éffaçent
			{
			SetCase(tab,feu->tab[j],feu->intens[j],largeur);
			}
		

		
		for(k=0;k<feu->nbFeu;k++) //On test à chaque fois si le robot n'est pas sur la COORD d'un foyer
			{
			if(((pompier->pos.x) == (feu->tab[k].x)) && ((pompier->pos.y) == (feu->tab[k].y))) // Si il est sur un feu
				{
				pompier->vie = pompier->vie - GetCase(tab,pompier->pos,largeur)+48; // Il perd le bon nombre de points de vie

				if(pompier->vie < 1) // Si il n'a plus de vie il meurt
					{
					printf("GAME OVER\n");
					exit(1);
					}

				if(GetCase(tab,pompier->pos,largeur)=='1' || GetCase(tab,pompier->pos,largeur)=='2' || GetCase(tab,pompier->pos,largeur)=='3') 
					{
					pompier->memoire.x = pompier->pos.x;  /* On garde la dernière position d'un 1 dans laquelle il est */
					pompier->memoire.y = pompier->pos.y;  /* passé pour pouvoir y retourner				  */
					pompier->survecu = 1; // Veut dire qu'il a déja survécu à un feu 

					if(pompier->porteur == 1)
						{
						StopFeu(feu,tab,largeur,pompier,hauteur);
						Show(tab,largeur,hauteur,pompier,graph);
						SDL_Delay(ATTENTE_FIN);
						exit(1);
						}
					}
				}
			}

		SetCase(tab,pompier->pos,'R',largeur); 
		Show(tab,largeur,hauteur,pompier,graph);
		usleep(VITESSE_ROBOT);
		temp = curs;
		}
	// Fin du while càd on est arrivé à la fin
	efface(tab,'.',hauteur,largeur); // On efface les points au cas ou il en reste
	pompier->porteur = 1; // Cette action est faite à chaque appel de la fonction, ce n'est pas trop grave
	return 1;
	}


/*************************************************************************/
/*			    Fonction RetourFeu				 */					
/*  Input :     Le tableau, le pompier, queue, hauteur, largeur	         */
/*		Les coordonnées des feux et la struct de type GRAPHIQUE	 */
/*  Objectif :  Retourner au feu si on est déjà passé dedans             */	
/* 		en reparcourant le tab des positions du départ à 	 */
/*		l'extincteur à l'envers				         */         
/*************************************************************************/
void RetourFeu(char * tab, POMPIER * pompier, QUEUE * q, int largeur, int hauteur, FEU * feu, GRAPHIQUE * graph)
	{
	int curs = q->back-1;
	while(1) // Pourrait être modifié mais on est sur et certain que le if va s'éxecuter
		{
		
		pompier->pos_old.x = pompier->pos.x;
		pompier->pos_old.y = pompier->pos.y;
		pompier->pos.x = q->Tab[curs].x;
		pompier->pos.y = q->Tab[curs].y;
		
		SetCase(tab,pompier->pos_old,' ',largeur);
		
		SetCase(tab,pompier->pos,'R',largeur);
		Show(tab,largeur,hauteur,pompier,graph);
		usleep(VITESSE_ROBOT);
       		curs = q->from[curs];
		pompier->pas++;
		if((pompier->pos.x == pompier->memoire.x) && (pompier->pos.y == pompier->memoire.y))
			{
			StopFeu(feu,tab,largeur,pompier,hauteur	);
			Show(tab,largeur,hauteur,pompier,graph);
			SDL_Delay(ATTENTE_FIN);
			exit(1);
			}
		}
	}


/*************************************************************************/
/*			    Fonction StopFeu				 */					
/*  Input :     Les coordonnées des feux, le tableau à  2 dim, largeur   */
/*		le robot pompier et la hauteur				 */
/*  Objectif :  Changer la valeur des feux pour tous les mettres à 0     */
/*		pour dire qu'ils sont éteints.				 */         
/*************************************************************************/
void StopFeu(FEU * feu, char * tab, int largeur, POMPIER * pompier, int hauteur)
	{
	int i = 0;
	for(i=0; i<feu->nbFeu; i++)
		{
		SetCase(tab,feu->tab[i],'0',largeur);
		SetCase(tab,pompier->pos,'R',largeur);
		}
	}


/*************************************************************************/
/*			    Fonction efface				 */					
/*  Input :     Le tableau à  2 dim, le caractère à effacer, la hauteur  */
/*		et la largeur						 */
/*  Objectif :  Efface toutes les apparitions du caractère dans le 	 */
/*		tableau à 2 dimensions					 */         
/*************************************************************************/
void efface(char * tab, char carac, int hauteur, int largeur)
	{
	int i = 0;
	int j = 0;
	for(j=0;j<hauteur;j++)
		{
 		for(i=0;i<largeur;i++)
			{
			COORD tmp;
			tmp.x = i;
			tmp.y = j;
			if((GetCase(tab,tmp,largeur) == carac) && (GetCase(tab,tmp,largeur) != 'H'))
				{
				SetCase(tab,tmp,' ',largeur);
				}
			}
		}
	}


/*************************************************************************/
/*			    Fonction AfficheTerm			 */					
/*  Input :     La hauteur, la largeur, le tableau à 2 dim et le robot   */
/*		pompier							 */
/*  Objectif :  Affiche la map dans le terminal	ainsi que le nombre      */
/*		de déplacement et la vie du pompier			 */         
/*************************************************************************/
void AfficheTerm(int hauteur, int largeur, char * tab, POMPIER * pompier)
	{
	int i,j;
	system("clear");
	for(j=0;j<hauteur;j++)
		{
 		for(i=0;i<largeur;i++)
			{
			COORD tmp;
			tmp.x = i;
			tmp.y = j;
			if(GetCase(tab,tmp,largeur)=='A') /* Je crée des "checkpoint" symbolisé par un A donc je ne veux */
				{			  /*        pas que l'utilisateur  puisse les voir	         */
				printf(" ");
				}
			else
				{
				printf("%c",GetCase(tab,tmp,largeur));
				}
			}
		printf("\n");
		}
	printf("Vie : %d Déplacements : %d\n",pompier->vie,pompier->pas);
	}

