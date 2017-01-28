#include "main.h"

//Fonction pour initialiser toute la SDL

int initialisation(GRAPHIQUE * graph, int hauteur, int largeur)
	{
	if( SDL_Init( SDL_INIT_VIDEO ) == -1 )
		{
		printf( "Can't init SDL:  %s\n", SDL_GetError( ) );
		return EXIT_FAILURE;
		}
 
	graph->ecran = SDL_SetVideoMode( TAILLE_CASE*largeur , TAILLE_CASE*hauteur+TAILLE_CASE*2, 32, SDL_HWSURFACE | SDL_RESIZABLE | SDL_DOUBLEBUF );

	if( graph->ecran == NULL )
		{
		printf( "Can't set video mode: %s\n", SDL_GetError( ) );
		return EXIT_FAILURE;
		}   

	SDL_WM_SetCaption("Mon joli robot !", NULL); //Titre de l'écran

	SDL_Flip(graph->ecran);
	
	graph->chemin = SDL_LoadBMP("CHEMIN.bmp");
	graph->mur = SDL_LoadBMP("MUR.bmp");
	graph->pacmanOuvert = SDL_LoadBMP("PACOUVERT.bmp");
	graph->pacmanFerme = SDL_LoadBMP("PACFERME.bmp");
	graph->feu = SDL_LoadBMP("FANTOME.bmp");
	graph->extincteur = SDL_LoadBMP("BONUS.bmp");
	graph->mort = SDL_LoadBMP("MORT.bmp");
	graph->feu2 = SDL_LoadBMP("FANTOME2.bmp");
	return EXIT_SUCCESS;
	}

//Fonction pour afficher la bonne texture en fonction de la case sur laquelle on est
void AfficheSDL(GRAPHIQUE * graph, COORD pos, SDL_Rect * rect_pos, char carac, char carac_old, SDL_Rect * rect_pos_old)
	{
	
	switch(carac)
		{
		case 'x' :
			SDL_BlitSurface(graph->mur, NULL, graph->ecran, rect_pos); 
			break;
		case 'D' :
			SDL_BlitSurface(graph->chemin, NULL, graph->ecran, rect_pos); 
			break;
		case 'E' :
			SDL_BlitSurface(graph->extincteur, NULL, graph->ecran, rect_pos); 
			break;
		case '1' :
		case '2' :
		case '3' :
			if(graph->act%2==1)SDL_BlitSurface(graph->feu, NULL, graph->ecran, rect_pos); 	
			else if(graph->act%2!=1)SDL_BlitSurface(graph->feu2, NULL, graph->ecran, rect_pos);  	
			break;
		case ' ' :
			SDL_BlitSurface(graph->chemin, NULL, graph->ecran, rect_pos); 
			break;
		case 'R' :
			if(graph->act%2==1)SDL_BlitSurface(graph->pacmanOuvert, NULL, graph->ecran, rect_pos); 	
			else if(graph->act%2!=1)SDL_BlitSurface(graph->pacmanFerme, NULL, graph->ecran, rect_pos); 
			graph->act++;
			break;
		case '0' :
			SDL_BlitSurface(graph->mort, NULL, graph->ecran, rect_pos); 			
		default :
			break;
		}

	}

//Fonction pour afficher toute la map en SDL
void AfficheTout(int hauteur, int largeur, GRAPHIQUE * graph, char * all, POMPIER * pompier)
	{
	int i,j;
	SDL_Rect rect_pos;
	SDL_Rect rect_pos_old;
	for(j=0;j<hauteur;j++)
		{
 		for(i=0;i<largeur;i++)
			{
			COORD tmp;
			tmp.x = i;
			tmp.y = j;
			rect_pos.x = rect_pos_old.x = TAILLE_CASE*i;
			rect_pos.y = rect_pos_old.y = TAILLE_CASE*j;
		
			AfficheSDL(graph,tmp,&rect_pos,GetCase(all,tmp,largeur),GetCase(all,pompier->pos_old,largeur),&rect_pos_old);
			}
		}
	graph->dejaAffiche = 1;

	}	

//Fonction pour afficher la texte en bas de la fenetre SDl (vie + déplacement)
void AfficheTexte(POMPIER * pompier, GRAPHIQUE * graph, int hauteur, int largeur)
	{
	TTF_Init();
	if(TTF_Init() == -1)
		{
   		fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
   		exit(EXIT_FAILURE);
		}

	TTF_Font *police = NULL;
	police = TTF_OpenFont("angelina.TTF", TAILLE_CASE*2);
	SDL_Color couleur = {255, 255, 0};
	

	SDL_Rect pos;
	char texte[30];

	//efface le texte pour ne pas réecrire dessus
	SDL_Rect positionEfface;
	positionEfface.x = 0;
	positionEfface.y = hauteur*TAILLE_CASE;
	positionEfface.w = largeur*TAILLE_CASE;
	positionEfface.h = TAILLE_CASE*2; //*2 pour avoir un espace assez grand
	
	SDL_FillRect(graph->ecran, &positionEfface, 0); //Warning de compil??

	//Vie
	sprintf(texte,"Vie: %d",pompier->vie);
	graph->texte = TTF_RenderText_Blended(police,texte, couleur);
	pos.x = TAILLE_CASE;
	pos.y = hauteur*TAILLE_CASE;
	SDL_BlitSurface(graph->texte, NULL, graph->ecran, &pos);

	//Pas
	sprintf(texte,"Nombre de pas : %d",pompier->pas);
	graph->texte = TTF_RenderText_Blended(police,texte, couleur);
	pos.x = TAILLE_CASE*8;
	pos.y = hauteur*TAILLE_CASE;
	SDL_BlitSurface(graph->texte, NULL, graph->ecran, &pos);
	
	
	TTF_CloseFont(police); 
	TTF_Quit();
	}

//Fonction au nom plutôt explicite
void JouerMusique(char * NomMusique)
	{
	SDL_WM_SetCaption("SDL_Mixer", NULL);

	if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1) //Initialisation de l'API Mixer
   		{
    		printf("%s", Mix_GetError());
  		}

  	Mix_Music *musique; //Création du pointeur de type Mix_Music
   	musique = Mix_LoadMUS("musique.mp3"); //Chargement de la musique
	
	if(musique == NULL)
		{
		printf("Erreur d'ouverture de la musique\n");
		}
	
   	Mix_PlayMusic(musique, -1); //Jouer infiniment la musique
	}
