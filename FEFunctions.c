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

	return 1;
}

int afficheMonde (Monde monde) {
	int x = 0;
	int y = 0;
	for (x=0; x<HAUT; x++) {
		printf("-------------------------------------------------------------------------------------------\n");
		for (y=0; y< LARG; y++) {
			printf("|");
			if (monde.plateau[x][y] == NULL) {
				printf("    ");	
			}
			else {
				printf("%c",monde.plateau[x][y]->couleur);
				printf("%c",monde.plateau[x][y]->arme);
				printf("%c",monde.plateau[x][y]->arme);
				printf("%c",monde.plateau[x][y]->arme);
			}
		}
		printf("|\n");
	}
	printf("-------------------------------------------------------------------------------------------\n");
	return 1;
}

Unite* insereUnite(Unite** unites, char couleur, char arme, int x, int y) {
	/*insere une unité dans une armée,
	défini son arme et ses coordonnées
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


	tmp->suiv = *unites;
	*unites = tmp;
	return tmp;
}
