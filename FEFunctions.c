#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

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
			monde->accessible[x][y] = false;
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

int secuScanInt() {
	/*scan et renvoie un entier avec une sécurité en cas d'input non voulu*/
	char line[256];
	int tmp = -1;

	while (true) {
		tmp = -1;

		if (fgets(line, sizeof(line), stdin)) {
    		if (1 == sscanf(line, "%d", &tmp)) {
        		/* input can be safely used */
        		return tmp;
     		}
		}
		printf("Erreur : veuillez entrer un int : ");
  	}
}

int lireCommande(int* x, int* y) {
	/*lit une paire de coordonées x et y 
	sur le plateau de manière sécurisée*/
	bool xValide = false;
	bool yValide = false;
	int tmp = -1;

	while (!xValide) {
		tmp = -1;
		printf("  - x : ");
		tmp = secuScanInt();
    	if (tmp >= 0 && tmp < HAUT) {
	  			*x = tmp;
	  			xValide = true;
	  		} else {
	  		printf("Erreur : entrez une valeur entre 0 et %d pour ", (HAUT-1));
	  	}
  	}

  	while (!yValide) {
		tmp = -1;
		printf("  - y : ");
		tmp = secuScanInt();
    	if (tmp >= 0 && tmp < HAUT) {
	  			*y = tmp;
	  			yValide = true;
	  		} else {
	  		printf("Erreur : entrez une valeur entre 0 et %d pour ", (LARG-1));
	  	}
  	}
  	return 1;
}

int dist(int a, int b, int c, int d) {
	/*donne la distance du point de coordonées a,b
	au point de coordonées c,d*/
	return (abs(a - c) + abs(b - d));
}

int estAProximite(Monde* monde, int x, int y, int maxDist) {
	/*remplie le tableau d'accessibilité du monde en fonction de 
	la case de référence (x,y) et de la distance d'atteinte*/
	int i = 0;
	int j = 0;
	for (i=0; i<HAUT; i++) {
		for (j=0; j<LARG; j++) {
			if (dist(x, y, i, j) <= maxDist) {
				monde->accessible[i][j] = true;
			} else {
				monde->accessible[i][j] = false;
			}
		}
	}
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
				printf("   ");	
			}
			else {
				printf("%c",monde.plateau[x][y]->couleur);
				printf("%c",monde.plateau[x][y]->arme);
				printf("%d",monde.plateau[x][y]->vie);
			}
			
			if (monde.accessible[x][y]) {
					printf("x");
			} else {
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

Unite* trouveUnite(Monde monde, int x, int y) {
	/*retourne l'unité présente sur une case du tableau*/
	return monde.plateau[x][y];
}

int supprimeUnite(Monde* monde, Unite* unite) {
	/*
	supprime l'unite de son armée et du plateau de jeu
	ne vérifie pas les paramètres
	*/
	/*
	/!!!\
	- penser à bien vérifier que le dernier élément 
	des listes d'unités des joueurs pointe vers un 0 
	sinon segfault
	/!!!\
	*/

	free(unite);
		
	unite->suiv = unite->suiv->suiv;
	monde->plateau[unite->posX][unite->posY] = NULL;
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











/*

   FONCTIONS OBSOLETES A SUPRIMER QUAND ON SERA SUR 

*/



int supprimeUniteDepuisMonde(Monde* monde, int x, int y) {
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

	if  (monde->plateau[x][y]->couleur == ROUGE) {
		/*check si l'unité est au joueur rouge*/
		unitesTmp = monde->rouge.unites;

		/*monde->rouge.nbUnites --;*/
	} 
	else if (monde->plateau[x][y]->couleur == BLEU) {
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

