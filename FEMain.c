#include "FEFunctions.h"
#include "FEStructures.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


int main () {

	/*string des charactères des couleurs et des armes, 
	pour pouvoir les obtenir grâce à in id numérique*/
	const char couleursChar[NBCOULEURS] ="RB";
	const char armesChar[NBARMES] = "HLEA";

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
	1 : sélectionner une unité
	2 : déplacer une unité
	3 : attaquer une unitée
	*/
	int a = 0; /*int pour identifier les armes*/
	int n = 0; /*int pour identifier le nombre d'unités*/
	int c = 0; /*int pour identifier la couleur*/
	int i = 0;
	int tmpX, tmpY;
	bool tmpCond;
	Unite* uniteTmp;
	Unite* uniteAlliee;
	Unite* uniteEnnemie;

	char couleurActive = 'R';
	int idCouleurActive = 0;

	initMonde(&monde);

	while(!jeuFini) {

		afficheMonde(monde);

		switch(etatDuJeu) {
			case(0): /*placement initial des unités sur le plateau*/
				commentaireIntro(); 
				
				for (a=0; a<NBARMES; a++) {
					for (n=0; n<monde.stats[a].nombre; n++) {
						for (c=0; c<NBCOULEURS; c++) {

							printf("  Joueur %s, entrez les coordonées de votre %s %d/%d\n",couleursMots[c],armesMots[a], (n+1),monde.stats[a].nombre);
							
							do {
								tmpX = -1;
								tmpY = -1;
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
				commentaireDebutBataille();
				etatDuJeu = 1;
				break;


			case(1): /*sélectionner une unité*/
				printf("  Joueur %s, choisissez une unité à déplacer.\n",couleursMots[idCouleurActive]);
				do {
					tmpX = -1;
					tmpY = -1;
					lireCommande(&tmpX, &tmpY);
					
					tmpCond = false;
					tmpCond = selectionnable(monde, couleurActive, tmpX, tmpY); 
					if (!tmpCond) {
						printf("  choisissez une unité de votre couleur\n");
					}
				} while (!tmpCond);

				uniteAlliee = trouveUnite(monde, tmpX, tmpY);
				etatDuJeu = 2;
				break;

			case(2):
				/*
				estAProximite(&monde, uniteAlliee->posX, uniteAlliee->posY, monde.stats[uniteAlliee->arme].endurance);
				afficheMonde(monde);
				printf("  Joueur %s, déplacez votre unité.\n",couleursMots[idCouleurActive]);
				*/
				printf("CA PASSE\n");
				etatDuJeu = 3;
				while (true);
				break;

			default: break;
		}

	}




	/* DEBUG CODE*/
	/*

	for (i=0; i<monde.stats[IDHACHE].nombre; i++) {
		printf("adding a unit\n");
		uniteTmp = creeUnite(ROUGE, HACHE,4,i, monde.stats[IDHACHE].vie);
		insereUnite(&monde.infosJoueurs[IDROUGE], uniteTmp);
		monde.plateau[4][i] = uniteTmp;
	}
	afficheMonde(monde);

	afficheListe(monde.infosJoueurs[IDROUGE]);
	uniteTmp = trouveUnite(monde,4,2);
	afficheListe(monde.infosJoueurs[IDROUGE]);
	supprimeUnite(&monde,uniteTmp);
	afficheListe(monde.infosJoueurs[IDROUGE]);
	afficheMonde(monde);

	uniteTmp = trouveUnite(monde,4,1);
	deplaceUnite(&monde,uniteTmp,5,1);

	afficheMonde(monde);
	lireCommande(&tmpX, &tmpY);

	printf("tmpX : %d, tmpY : %d\n", tmpX, tmpY);
	estAProximite(&monde, tmpX,tmpY,4);
	afficheMonde(monde);
	*/
	return 0;
}