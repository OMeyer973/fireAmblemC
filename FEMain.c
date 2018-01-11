#include "FEFunctions.h"
#include "FEStructures.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


int main () {

	/*string des charactères des couleurs et des armes, 
	pour pouvoir les obtenir grâce à in id numérique*/
	char couleursChar[NBCOULEURS] ="RB";
	char armesChar[NBARMES] = "HLEA";

	/*tableau de string des mots des couleurs et des armes 
	pour écrire des commentaires à partir des ID*/
	const char *couleursMots[NBARMES];
	couleursMots[0] = "rouge";
	couleursMots[1] = "bleu";

	const char *armesMots[NBARMES];
	armesMots[0] = "hache";
	armesMots[1] = "lance";
	armesMots[2] = "epee";
	armesMots[3] = "arc";
	
	Monde monde;
	bool jeuFini = false;
	int etatDuJeu = 0;
	/*
	0 : placement des amrées sur le plateau
	*/
	int a = 0;
	int n = 0;
	int c = 0;
	int i = 0;
	int tmpX, tmpY;
	Unite* uniteTmp;

	initMonde(&monde);
	
	while(!jeuFini) {

		afficheMonde(monde);

		switch(etatDuJeu) {
			case(0):
				commentaireIntro(); 
				
				for (a=0; a<NBARMES; a++) {
					for (n=0; n<monde.stats[a].nombre; n++) {
						for (c=0; c<NBCOULEURS; c++) {

							printf("  Joueur %s, entrez les coordonées de votre %s %d/%d\n",couleursMots[c],armesMots[a], (n+1),monde.stats[a].nombre);
							
							do {
								lireCommande(&tmpX, &tmpY);
								
								if (!estLibre(monde, tmpX, tmpY)) {
									printf("  choisissez une case vide\n");
								}
							
							} while (!estLibre(monde, tmpX, tmpY));

							uniteTmp = creeUnite(couleursChar[c], armesChar[a],tmpX,tmpY, monde.stats[a].vie);
							insereUnite(&monde.infosJoueurs[c], uniteTmp);
							poseUnite(&monde, uniteTmp, tmpX, tmpY);

								
							afficheMonde(monde);
						}
					}
				}
				afficheMonde(monde);

			break;
		}

	}
	




	/* DEBUG CODE*/


	for (i=0; i<monde.stats[IDHACHE].nombre; i++) {
		uniteTmp = creeUnite(ROUGE, HACHE,4,i, monde.stats[IDHACHE].vie);
		insereUnite(&monde.infosJoueurs[IDROUGE], uniteTmp);
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