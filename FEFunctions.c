#include <stdio.h>
#include <stdlib.h>

#include "FEStructures.h"
#include "FEFunctions.h"


int initMonde (Monde* monde) {
	monde->tour = 0;

	/*init plateau*/
	int x = 0;
	int y = 0;
	for (x=0; x<HAUT; x++) {
		for (y=0; y< LARG; y++) {
			monde->plateau[x][y] = NULL;
			}
		}

	/*definition des stats*/
	monde->stats.hache.nombre 	= 3;
	monde->stats.hache.endurance= 3;
	monde->stats.hache.portee 	= 1;
	monde->stats.hache.vie 		= 7;
	monde->stats.hache.force 	= 4;

	monde->stats.lance.nombre 	= 3;
	monde->stats.lance.endurance= 5;
	monde->stats.lance.portee 	= 2;
	monde->stats.lance.vie 		= 6;
	monde->stats.lance.force 	= 2;

	monde->stats.epee.nombre 	= 3;
	monde->stats.epee.endurance	= 4;
	monde->stats.epee.portee 	= 1;
	monde->stats.epee.vie 		= 6;
	monde->stats.epee.force 	= 3;

	monde->stats.arc.nombre 	= 4;
	monde->stats.arc.endurance 	= 3;
	monde->stats.arc.portee 	= 4;
	monde->stats.arc.vie 		= 5;
	monde->stats.arc.force 		= 3;

	Unite uniteTmp;
	uniteTmp.suiv = 0;
	monde->rouge.unites = &uniteTmp;
	monde->bleu.unites = &uniteTmp;
	return 1;
}

int afficheDeuxChiffres (int x) {
	/*affiche x écrit avec 2 chiffres (on suppose x < 100)*/
	if (x<10) {
		printf("0%d",x);
	} else {
		printf("%d",x);
	}
	return 1;
}


int afficheMonde (Monde monde) {
	int x = 0;
	int y = 0;
	
	/*affiche numéro des colones*/
	printf("\n  y");
	for (y=0; y< LARG; y++) {
		printf(" ");
		afficheDeuxChiffres(y);
		printf("  ");
	}
	printf("\n");

	printf("x -------------------------------------------------------------------------------------------\n");
	
	for (x=0; x<HAUT; x++) {
		afficheDeuxChiffres(x);

		for (y=0; y< LARG; y++) {
			printf("|");
			if (monde.plateau[x][y] == NULL) {
				printf("    ");	
			}
			else {
				printf("%c",monde.plateau[x][y]->couleur);
				printf("%c",monde.plateau[x][y]->arme);
				printf("%d",monde.plateau[x][y]->vie);
				printf(" ");
			}
		}
		printf("|\n");
		printf("  -------------------------------------------------------------------------------------------\n");
		
	}
	return 1;
}

Unite* creeUnite(char couleur, char arme, int x, int y, int vie) {
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

int supprimeUnite(Monde* monde, int x, int y) {
	/*
	suprime de la liste unites 
	l'unite se trouvant sur la plateau aux coordonées  x y
	ne vérifie pas les paramètres
	*/
	/*
	/!!!\
	- penser à bien vérifier que le dernier élément 
	des listes d'unités des joueurs pointe vers un 0 
	sinon segfault
	- ne pas exécuter sur une case vide sinon segfault
	/!!!\
	*/

	Unite* unitesTmp;

	if  (monde->plateau[x][y]->couleur =='R') {
		/*check si l'unité est au joueur rouge*/
		unitesTmp = monde->rouge.unites;

		/*monde->rouge.nbUnites --;*/
	} 
	else if (monde->plateau[x][y]->couleur =='B') {
		/*check si l'unité est au joueur bleu*/
		unitesTmp = monde->bleu.unites;

		monde->bleu.nbUnites --;
	}

	/*retire l'unité de la liste*/
	while (unitesTmp->suiv != 0){
		if (unitesTmp->posX == x && unitesTmp->posY == y) {
			
			free(unitesTmp);
			
			unitesTmp->suiv = unitesTmp->suiv->suiv;
			monde->plateau[x][y] = NULL;
			return 1;
		}
		unitesTmp = unitesTmp->suiv;
	}
	return 0;
}

Unite* trouveUnite(Monde monde, int x, int y) {
	/*retourne l'unité présente sur une case du tableau*/
	return monde.plateau[x][y];
}

int deplaceUnite (Monde* monde, Unite* unite, int x, int y) {
	/*déplace une unité vers une nouvelle position sur le plateau*/
	monde->plateau[unite->posX][unite->posY] = NULL;
	unite->posX = x;
	unite->posY = y;
	monde->plateau[x][y] = unite;
	return 1;
}