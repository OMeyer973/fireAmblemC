#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <MLV/MLV_all.h>
#include <unistd.h>

#include "FEStructures.h"
#include "FEFunctions.h"


int initMonde (Monde* monde) {
	monde->infoJeu.tour = 0;
	monde->infoJeu.etatDuJeu = 0;
	monde->infoJeu.couleurActive = 0;

	/*init plateau*/
	int x = 0;
	int y = 0;
	for (x=0; x<HAUT; x++) {
		for (y=0; y< LARG; y++) {
			monde->plateau[x][y] = NULL;
			monde->accessible[x][y] = false;
			}
		}

	/*definition des stats*/
	monde->stats[IDHACHE].nombre 	= 2;
	monde->stats[IDHACHE].endurance = 3;
	monde->stats[IDHACHE].portee 	= 1;
	monde->stats[IDHACHE].vie 		= 7;
	monde->stats[IDHACHE].force 	= 4;

	monde->stats[IDLANCE].nombre 	= 2;
	monde->stats[IDLANCE].endurance = 5;
	monde->stats[IDLANCE].portee 	= 2;
	monde->stats[IDLANCE].vie 		= 6;
	monde->stats[IDLANCE].force 	= 2;

	monde->stats[IDEPEE].nombre 	= 2;
	monde->stats[IDEPEE].endurance	= 4;
	monde->stats[IDEPEE].portee 	= 1;
	monde->stats[IDEPEE].vie 		= 6;
	monde->stats[IDEPEE].force 		= 3;

	monde->stats[IDARC].nombre 		= 3;
	monde->stats[IDARC].endurance 	= 3;
	monde->stats[IDARC].portee 		= 4;
	monde->stats[IDARC].vie 		= 5;
	monde->stats[IDARC].force 		= 3;


	monde->textes.couleursMots[0] = "rouge";
	monde->textes.couleursMots[1] = "bleu";
	monde->textes.couleursChar = "RB";

	monde->textes.armesMots[0] = "hache";
	monde->textes.armesMots[1] = "lance";
	monde->textes.armesMots[2] = "epee";
	monde->textes.armesMots[3] = "arc";
	monde->textes.armesChar = "HLEA";

	/* initialise les chemins des sprites des unités */

	monde->textes.tab_chemin_rouge[0] = "img/sprite/rouge/hache.png";
	monde->textes.tab_chemin_rouge[1] = "img/sprite/rouge/lance.png";
	monde->textes.tab_chemin_rouge[2] = "img/sprite/rouge/epee.png";
	monde->textes.tab_chemin_rouge[3] = "img/sprite/rouge/arc.png";
	monde->textes.tab_chemin_bleu[0] = "img/sprite/bleu/hache.png";
	monde->textes.tab_chemin_bleu[1] = "img/sprite/bleu/lance.png";
	monde->textes.tab_chemin_bleu[2] = "img/sprite/bleu/epee.png";
	monde->textes.tab_chemin_bleu[3] = "img/sprite/bleu/arc.png";

	/* initialise le chemin de l'image de fond de plateau, de l'UI et des images renseignant le joueur actif */

	monde->textes.chemin_plateau = "img/plateauv3.png";
	monde->textes.chemin_infos = "img/UI.png";
	monde->textes.tab_chemin_joueurActif[0] = "img/actif/joueurActifRouge.png";
	monde->textes.tab_chemin_joueurActif[1] = "img/actif/joueurActifBleu.png";

	/* Initialise le chemin des images indiquant la phase en cours du jeu */
	monde->textes.tab_chemin_phase[0] = "img/phase/phasePlacement.png";
	monde->textes.tab_chemin_phase[1] = "img/phase/phaseSelection.png";
	monde->textes.tab_chemin_phase[2] = "img/phase/phaseDeplacement.png";
	monde->textes.tab_chemin_phase[3] = "img/phase/phaseAttaque.png";

	
	int i, j;
	Unite* uniteTmp;

	
	int decors[LARG][HAUT] =  {{1,1,0,0,1,1,1,1,1,0,0,0},
								{0,0,0,0,1,1,1,1,0,0,0,0},
								{0,0,0,0,1,1,1,0,0,0,0,0},
								{0,0,0,0,0,1,1,0,0,0,0,0},
								{0,0,0,0,0,0,0,0,0,0,0,0},
								{0,0,0,0,1,0,0,0,0,0,0,1},
								{0,0,0,1,1,1,0,0,0,1,1,1},
								{1,0,0,1,1,1,1,1,1,1,1,1},
								{1,0,0,0,0,0,1,1,1,1,0,0},
								{0,0,1,0,0,0,0,1,1,0,0,0},
								{0,1,1,1,0,0,0,0,0,0,0,1},
								{1,1,1,1,0,0,0,0,0,0,0,1},
								{1,1,1,1,0,0,0,0,0,0,1,1},
								{1,1,1,1,1,0,0,0,0,0,1,1},
								{1,1,1,1,1,0,0,0,0,0,1,1},
								{1,1,1,1,1,1,0,0,1,1,0,1},
								{1,1,1,1,1,1,0,1,1,1,0,1},
								{1,1,1,1,1,1,0,1,1,1,0,0}};

	for (i=0; i<LARG; i++) {
		for (j=0;j<HAUT; j++) {
			if (decors[i][j]) {
			uniteTmp = creeUnite(2, HACHE,j,i,1000);
			monde->plateau[j][i] = uniteTmp;
			}
		}
	}
	
	/*init unites & decors*/
	monde->infosJoueurs[IDROUGE].unites = NULL;
	monde->infosJoueurs[IDBLEU].unites = NULL;
	monde->infosJoueurs[IDROUGE].nbUnites = 0;
	monde->infosJoueurs[IDBLEU].nbUnites = 0;
	monde->infosJoueurs[IDROUGE].nbEndormis = 0;
	monde->infosJoueurs[IDBLEU].nbEndormis = 0;
	
	return 1;
}


int dist(int a, int b, int c, int d) {
	/*donne la distance du point de coordonées a,b
	au point de coordonées c,d*/
	return (abs(a - c) + abs(b - d));
}

int videAccessibilite(Monde* monde) {
	/*vide le tableau d'accessibilité*/
	int i = 0;
	int j = 0;
	for (i=0; i<HAUT; i++) {
		for (j=0; j<LARG; j++) {
			monde->accessible[i][j] = false;
		}
	}
	return 1;
}


int dessinePlateau(Monde monde){
	/* Ouvre une fenêtre MLV et dessine la carte + la barre information */
	int width = 1300, height = 600;
	MLV_create_window( "Fire Emblem", "v3", width, height );
	MLV_Image* plateau = MLV_load_image( monde.textes.chemin_plateau );
	if( ! plateau){
		fprintf(
			stderr, "Impossible de charger l'image %s.\n",
			monde.textes.chemin_plateau
		);
		exit(0);
	}
	MLV_draw_image(plateau, 0,0);
	MLV_actualise_window();
	MLV_free_image( plateau );
	return 1;
}

int actualiseJeu(Monde* monde){
	/* Met à jour la position des unités ainsi que leur barre de vie */
	int x, y;
	const char* chemin_plateau = "img/plateauv3.png";
	MLV_Image* plateau = MLV_load_image( chemin_plateau );
	if( ! plateau){
		fprintf(
			stderr, "Impossible de charger l'image %s.\n",
			chemin_plateau
		);
		exit(0);
	}
	MLV_draw_image(plateau, 0,0);
	for (x=0; x<HAUT; x++){ /* On parcourt le tableau des unités et si une unité est présente, on la dessine avec ses hps */
		for (y=0; y<LARG; y++){
			if( monde->plateau[x][y] != NULL ){
				dessineUnite(*monde, monde->plateau[x][y]->couleur,monde->plateau[x][y]->arme, x, y, monde->plateau[x][y]->vie);
				if( monde->plateau[x][y]->dort ) {
					MLV_draw_filled_rectangle(y*pixelsParCase, x*pixelsParCase, 50,50, MLV_rgba(0,0,0,60));
				}
				dessineBarreVie(monde, *(monde->plateau[x][y]));
			}
		}
	}

	MLV_actualise_window();
	MLV_free_image( plateau );
	return 1;
}

int reinitialiseInfos(Monde monde, int idJoueurActif, int idPhaseActuelle){
	/* Réinitialise le contenu de la barre d'information en y intégrant le joueur actif et la phase actuelle */
	
	MLV_Image* infos = MLV_load_image( monde.textes.chemin_infos );
	if( ! infos ){
		fprintf(
			stderr, "Impossible de charger l'image %s.\n",
			monde.textes.chemin_infos
		);
		exit(0);
	}
	/* prepare l'image relative au joueur actif en haut de l'UI */
	MLV_Image* joueurActif = MLV_load_image( monde.textes.tab_chemin_joueurActif[idJoueurActif] );
	if( ! joueurActif){
		fprintf(
			stderr, "Impossible de charger l'image %s.\n",
			monde.textes.tab_chemin_joueurActif[idJoueurActif]
		);
		exit(0);
	}
	/* prepare l'image relative à la phase active en bas de l'UI */
	MLV_Image* phaseActuelle = MLV_load_image( monde.textes.tab_chemin_phase[idPhaseActuelle] );
	if( ! phaseActuelle){
		fprintf(
			stderr, "Impossible de charger l'image %s.\n",
			monde.textes.tab_chemin_phase[idPhaseActuelle]
		);
		exit(0);
	}
	/* Dessine le tout puis libère la mémoire */
	MLV_draw_image(infos, 900,0);
	MLV_draw_image(joueurActif, 900,0);
	MLV_draw_image(phaseActuelle, 900,80);
	MLV_free_image(infos);
	MLV_free_image(joueurActif);
	MLV_free_image(phaseActuelle);
	return 1;
}

int prepareInfosIntro(Monde* monde, int couleurActive, int armesActive){
	/* Prépare le texte destiné à être affiché dans la barre d'information 
	en début de partie (phase 0) et l'envoie à la fonction afficheInfos */

	char tmpInfos[350];

	strcpy (tmpInfos,"     ==========================\n       Bienvenue dans FELite.\n     ==========================\n\n\nAvant de commencer la bataille, les 2 joueurs doivent\n placer leurs armées sur le champs de bataille.\n Chaque joueur a à sa disposition :\n 2 Haches, 2 Lances, 2 Epees et 3 Arc.\n\n\n Placez votre ");
	strcat (tmpInfos, monde->textes.armesMots[armesActive]);
	
	afficheInfos(tmpInfos);

	return 1;
}

int prepareInfosResultAttaque(Monde* monde, int ptDegat, int valeurCase){
	/* Prépare le texte destiné à être affiché dans la barre d'information 
	pour indiquer le résultat de la bataille (phase 4) et l'envoie à la fonction afficheInfos */

	char tmpInfos[300];
	char tmpConversion[80];

	strcpy (tmpInfos,"Votre arme s'abat sur l'ennemi et lui inflige\n ");
	sprintf(tmpConversion, "%d", ptDegat);
	strcat (tmpInfos, tmpConversion);
	strcat(tmpInfos,"pt de dégat.");

	if(valeurCase == 0){ /* Si une unité est morte, on incrémente des informations concernant les unités restantes */
		strcat(tmpInfos,"\n\n\nL'unité est morte.");
		strcat (tmpInfos, "\n\n\n Il reste ");
		sprintf(tmpConversion, "%d", monde->infosJoueurs[IDROUGE].nbUnites);
		strcat (tmpInfos, tmpConversion);
		strcat(tmpInfos," unites au joueur ");
		strcat (tmpInfos, monde->textes.couleursMots[IDROUGE]);
		strcat(tmpInfos," et\n ");
		sprintf(tmpConversion, "%d", monde->infosJoueurs[IDBLEU].nbUnites);
		strcat (tmpInfos, tmpConversion);
		strcat(tmpInfos," unites au joueur ");
		strcat (tmpInfos, monde->textes.couleursMots[IDBLEU]);
	}

	afficheInfos(tmpInfos);

	return 1;
}

int prepareInfosFinPartie(char* perdant, char* gagnant){
	char tmpInfos[300];

	strcpy (tmpInfos,"L'armée du joueur ");
	strcat (tmpInfos, perdant);
	strcat(tmpInfos," est vaincue.\n\n Le joueur ");
	strcat (tmpInfos, gagnant);
	strcat(tmpInfos," remporte la victoire !");

	afficheInfos(tmpInfos);

	return 1;
}


int afficheInfos(char* texte){
	/* Fonction qui affiche dans la barre information le texte récupéré et prêt à être affiché */
	int taille_interlinge = 0;
	MLV_draw_text_box(
		900,150,
		400,450,
		texte,
		taille_interlinge,
		MLV_rgba(0,0,0,0), MLV_COLOR_WHITE, MLV_rgba(0,0,0,0),
		MLV_TEXT_CENTER,
		MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER
	);
	MLV_actualise_window();
	return 1;
}

int dessineUnite(Monde monde, int couleur,int idarme, int x, int y, int vie){
	/* Dessine les unités sur le plateau avec la bonne couleur 
	et en fonction des coordonnées du clic */
	int i, posX, posY;

	posX = x * pixelsParCase; /* On convertit les valeurs de cases en valeur pixels */
	posY = y * pixelsParCase;

	for(i=0; i< NBARMES; i++){ /* On boucle pour trouver le bon chemin du sprite en fonction de l'unité et de sa couleur */
		if(idarme == i){
			if(couleur == 0){
				MLV_Image* initialisation = MLV_load_image( monde.textes.tab_chemin_rouge[i] );
				if( ! initialisation ){
					fprintf(
						stderr, "Impossible de charger l'image %s.\n",
						monde.textes.tab_chemin_rouge[i]
					);
					exit(0);
				}
				MLV_draw_image(initialisation, posY, posX);
				MLV_actualise_window();
				MLV_free_image( initialisation );
			}
			else{
				MLV_Image* initialisation = MLV_load_image( monde.textes.tab_chemin_bleu[i] );
				if( ! initialisation ){
					fprintf(
					stderr, "Impossible de charger l'image %s.\n",
					monde.textes.tab_chemin_bleu[i]
					);
				exit(0);
				}
				MLV_draw_image(initialisation, posY, posX);
				MLV_actualise_window();
				MLV_free_image( initialisation );
			}
		}
	}
	return 1;
}

int dessineBarreVie(Monde* monde, Unite unite){
	/* Dessine les barres de vie des unités en fonction de leur position et de leur vie actuelle */
	if (unite.couleur<2) {
		char tmpInfos[80];
		char tmpConversion[80];
		int posBarreVieX, posBarreVieY, posTexteBarreVieX, posTexteBarreVieY, tailleBarreVie;

		/* On prépare l'affichage des pvrestant/initiaux */
		sprintf(tmpConversion, "%d", monde->plateau[unite.posX][unite.posY]->vie);
		strcpy (tmpInfos, tmpConversion);
		strcat (tmpInfos, "/");
		sprintf(tmpConversion, "%d", monde->stats[unite.arme].vie);
		strcat (tmpInfos, tmpConversion);

		/* on place les éléments au dessus de l'unité */
		posBarreVieX = (unite.posX*pixelsParCase) + 3;
		posBarreVieY = (unite.posY*pixelsParCase) + 5;
		posTexteBarreVieX = posBarreVieX - 5;
		posTexteBarreVieY = posBarreVieY + 25;
		tailleBarreVie = 25 - (4 * ( monde->stats[unite.arme].vie - unite.vie ) ) ;

		/* On dessine le tout */
		MLV_draw_rectangle( posBarreVieY, posBarreVieX, 25, 5, MLV_COLOR_GREEN );
		MLV_draw_filled_rectangle( posBarreVieY, posBarreVieX, tailleBarreVie, 5, MLV_COLOR_GREEN );
		MLV_draw_text_box(
			posTexteBarreVieY,posTexteBarreVieX,
			35,35,
			tmpInfos,
			0,
			MLV_rgba(0,0,0,0), MLV_COLOR_WHITE, MLV_rgba(0,0,0,0),
			MLV_TEXT_LEFT,
			MLV_HORIZONTAL_LEFT, MLV_VERTICAL_TOP
		);
	}
	return 1;
}

bool verifClicValide(int* posX, int* posY){
	/* Verifie si le clic est bien sur une case du plateau */
	int x,y;
	if( MLV_get_mouse_button_state( MLV_BUTTON_LEFT ) == MLV_PRESSED ){
			MLV_get_mouse_position( &y, &x );
			*posX = x / pixelsParCase;
			*posY = y / pixelsParCase;
			if(*posX <= HAUT && *posY <= LARG){
				return true;
			}
		return false;
	}
	return false;
}

bool selectionnable(Monde monde, int couleur, int x, int y) {
	/*renvoie vrai si la case sélectionnée contient une unité sélectionnable
	par le joueur d'une la couleur*/
	if ((monde.plateau[x][y] != NULL) && 
		(monde.plateau[x][y]->couleur == couleur) &&
		(!monde.plateau[x][y]->dort)) {
		return true;
	} 
	return false;
}

int dessineAccessibilite(Monde* monde, int x, int y, int maxDist){
	/* Entoure de vert les cases sur lesquelles l'unité peut se rendre */
	int i = 0;
	int j = 0;
	for (i=0; i<HAUT; i++) {
		for (j=0; j<LARG; j++) {
			if ( 	((dist(x, y, i, j) <= maxDist) && (monde->plateau[i][j] == NULL))
				 	|| (i == x && j == y) )  {
				monde->accessible[i][j] = true;
				if( (i != x) || (j != y) ){
					MLV_draw_rectangle( j*pixelsParCase, i*pixelsParCase, 50, 50, MLV_COLOR_GREEN );
				}	
			} else {
				monde->accessible[i][j] = false;
			}
		}
	}
	MLV_actualise_window();
	return 1;
}

int dessineAccessibiliteAttaque(Monde* monde, int x, int y, int maxDist, int couleur){
	/* Entoure en rouge les unités adverses que l'unité venant d'être déplacée peut attaquer */
	int i = 0;
	int j = 0;
	int count = 0;
	for (i=0; i<HAUT; i++) {
		for (j=0; j<LARG; j++) {
			if (((dist(x, y, i, j) <= maxDist) 
				&& (monde->plateau[i][j] != NULL)
				&& (couleur != monde->plateau[i][j]->couleur)
				&& (monde->plateau[i][j]->couleur < 2))
				|| (i == x && j == y))
				{
				monde->accessible[i][j] = true;
				if( ((i != x) || (j != y)) ){ 
					MLV_draw_rectangle( j*pixelsParCase, i*pixelsParCase, 50, 50, MLV_COLOR_RED );
					count++; /* On compte le nombre d'ennemie à portée. S'il est égal à 0, le main passe le tour directement */
				}
			} else {
				monde->accessible[i][j] = false;
			}

		}
	}
	MLV_actualise_window();
	return count;
}

int affichageDegat(int x, int y, int ptDegat){
	/* Fonction qui permet d'afficher les dégâts infligés à l'unité à côté de sa barre de vie */
	char tmpInfos[120];
	char tmpConversion[120];
	int posX, posY;

	/* On positionne l'affichage */
	posX = (x*pixelsParCase) - 3;
	posY = (y*pixelsParCase) + 50;

	/* On le met en forme */
	strcpy (tmpInfos,"-");
	sprintf(tmpConversion, "%d", ptDegat);
	strcat (tmpInfos, tmpConversion);

	/* On le dessine */
	MLV_draw_text_box(
		posY, posX,
		35,35,
		tmpInfos,
		0,
		MLV_rgba(0,0,0,0), MLV_COLOR_RED, MLV_rgba(0,0,0,0),
		MLV_TEXT_LEFT,
		MLV_HORIZONTAL_LEFT, MLV_VERTICAL_TOP
	);
	MLV_actualise_window();
	sleep(1);
	return 1;
}


Unite* creeUnite(int couleur, int arme, int x, int y, int vie) {
	/*créé une unité,
	défini son arme ses coordonnées
	et retourne l'adresse de l'unite
	On ne fait pas de vérification sur les paramètres*/
	Unite* tmp;
	
	tmp = malloc(sizeof(Unite));
	if (tmp==NULL){
        printf("l'allocation n'a pas fonctionné");
    	return 0;
	}
    
    tmp->arme = arme;
    tmp->couleur = couleur;
    tmp->posX = x;
    tmp->posY = y;
    tmp->vie = vie;
    tmp->dort = false;
    tmp->suiv = NULL;

	return tmp;
}

int insereUnite(InfoJoueur* joueur, Unite* unite) {
	/*insere une unité dans une armée 
	et incrémente le nombre d'unités du joueur*/
	unite->suiv = joueur->unites;
	joueur->unites = unite;
	
	joueur->nbUnites ++;
	return 1;
}

Unite* trouveUnite(Monde monde, int x, int y) {
	/*retourne l'unité présente sur une case du tableau*/
	return monde.plateau[x][y];
}


int supprimeUnite(Monde * monde, Unite * unite){
	
	/*bug : fais des segfaults pour les listes de nb <= 2*/

	int x = unite -> posX, y = unite -> posY;
	int color = unite -> couleur;

	UListe tmp, prev;

	if ((tmp = malloc(sizeof(Unite))) == NULL){
		printf("malloc error\n");
		exit(EXIT_FAILURE);
	}

	tmp = monde->infosJoueurs[color].unites;
	monde->infosJoueurs[color].nbUnites--;

	if (tmp != NULL && ((tmp->posX == x) && (tmp->posY == y))){
		monde -> infosJoueurs[color].unites = monde -> infosJoueurs[color].unites -> suiv;
		free(tmp);
		monde -> plateau[x][y] = NULL;
		return 1;
	}

	prev = tmp;
	while (tmp != NULL && (tmp->posX != x || tmp->posY != y)){
		prev = tmp;
		tmp = tmp -> suiv;
	}

	if (tmp == NULL){
		printf("Unit was not in Linked List !\n");
		return -1;
	}
	
	prev -> suiv = tmp -> suiv;
	free(tmp);
	monde -> plateau[x][y] = NULL;
	return 1;
}

int poseUnite (Monde* monde, Unite* unite, int x, int y) {
	/*pose une unité sur une case du plateau
	Attention : si l'unité est déjà présente sur le plateau, 
	elle sera présente en double !*/
	unite->posX = x;
	unite->posY = y;
	monde->plateau[x][y] = unite;
	return 1;
}

int leveUnite (Monde* monde, Unite* unite) {
	/*retire une unité du plateau 
	sans la supprimer de l'armée du joeur
	pré-requis : l'unité est bien présente sur le plateau.*/
	monde->plateau[unite->posX][unite->posY] = NULL;
	return 1;
}

int deplaceUnite (Monde* monde, Unite* unite, int x, int y) {
	/*déplace une unité vers une nouvelle position sur le plateau*/
	leveUnite (monde, unite);
	poseUnite (monde, unite, x, y); 
	return 1;
}

int blesseUnite (Monde* monde, Unite* unite, int degat) {
	/*blesse une unité d'un certain nombre de points de dégat
	et la supprime si elle n'a plus de points de vie*/
	unite->vie -= degat;
	if (unite->vie <= 0) {
			supprimeUnite(monde,unite);
	}
	return 1;
}

bool estLibre(Monde monde, int x, int y) {
	/*renvoie vrai si la case x,y est libre*/
	if (monde.plateau[x][y] == NULL) {
		return true;
	}
	return false;
}

int endorsUnite(Monde* monde, Unite* unite) {
	/*endors l'unité donnée en paramètre 
	et met à jour le nb d'unités endormies de cette couleur*/
	unite->dort = true;
	monde->infosJoueurs[unite->couleur].nbEndormis ++;
	return 1;
}

int reveilleUnites(Monde* monde, int couleur) {
	UListe tmp;

	if ((tmp = malloc(sizeof(Unite))) == NULL){
		printf("malloc error\n");
		exit(EXIT_FAILURE);
	}

	tmp = monde->infosJoueurs[couleur].unites;

	while (tmp != NULL) {
		tmp->dort = false;
		tmp = tmp->suiv;
	}

	free(tmp);

	monde->infosJoueurs[couleur].nbEndormis = 0;
	return 1;
}

int videMonde(Monde* monde){
	int i,j;
	for (i=0; i<HAUT; i++) {
		for (j=0; j<LARG; j++) {
			if( monde->plateau[i][j] != NULL ){
				free(monde->plateau[i][j]);
				monde->plateau[i][j] = NULL;
			}	
		}
	}
	return 1;
}