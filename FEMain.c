#include "FEFunctions.h"
#include "FEStructures.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


int main () {
	Monde monde;
	bool jeuFini = false;
	int etatDuJeu = 0;
	/*
	0 : placement des amrées sur le plateau
	*/

	int i = 0;
	int tmpX, tmpY;
	Unite* uniteTmp;

	initMonde(&monde);
	
	while(!jeuFini) {

		afficheMonde(monde);

		switch(etatDuJeu) {
			case(0):

				printf("  Bienvenue dans FELite. Avant de commencer la bataille, les 2 joueurs doivent placer\n  leurs armées sur le champs de bataille.\n");
				printf("  Chaque joueur a à sa disposition une armée composée de 3 Haches, 3 Lances, 3 Epees et 4 Arcs\n");

				/*POSER LES HACHES*/
				for (i=0; i<monde.stats.hache.nombre; i++) {
					/*POSER HACHE ROUGE*/
					printf("  Joueur Rouge, entrez les coordonées de votre Hache %d/%d\n",(i+1),monde.stats.hache.nombre);

					lireCommande(&tmpX, &tmpY);
					uniteTmp = creeUnite(ROUGE, HACHE,tmpX,tmpY, monde.stats.hache.vie);
					insereUnite(&monde.rouge, uniteTmp);
					poseUnite(&monde, uniteTmp, tmpX, tmpY);
					afficheMonde(monde);

					/*POSER HACHE BLEU*/
					printf("  Joueur bleu, entrez les coordonées de votre Hache %d/%d\n",(i+1),monde.stats.hache.nombre);

					lireCommande(&tmpX, &tmpY);
					uniteTmp = creeUnite(BLEU, HACHE,tmpX,tmpY, monde.stats.hache.vie);
					insereUnite(&monde.bleu, uniteTmp);
					poseUnite(&monde, uniteTmp, tmpX, tmpY);
					afficheMonde(monde);
				}
				afficheMonde(monde);

			break;
		}

	}
	




	/* DEBUG CODE*/


	for (i=0; i<monde.stats.hache.nombre; i++) {
		uniteTmp = creeUnite(ROUGE, HACHE,4,i, monde.stats.hache.vie);
		insereUnite(&monde.rouge, uniteTmp);
		monde.plateau[4][i] = uniteTmp;
	}
	afficheMonde(monde);

	uniteTmp = trouveUnite(monde,4,2);
	supprimeUnite(&monde,uniteTmp);
	afficheMonde(monde);

	uniteTmp = trouveUnite(monde,4,1);
	deplaceUnite(&monde,uniteTmp,5,1);

	afficheMonde(monde);
	lireCommande(&tmpX, &tmpY);

	printf("tmpX : %d, tmpY : %d\n", tmpX, tmpY);
	estAProximite(&monde, tmpX,tmpY,4);
	afficheMonde(monde);
	
	return 0;
}