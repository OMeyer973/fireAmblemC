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

	int tmpX, tmpY;
	int ptDegat;
	bool entreeOk;
	Unite* uniteTmp;
	Unite* uniteJoueur;
	Unite* uniteCible;

	char couleurActive = 'R';
	int idCouleurActive = 0;

	initMonde(&monde);

	afficheMonde(monde, armesChar);
	while(!jeuFini) {

		switch(etatDuJeu) {
			case(0): /*placement initial des unités sur le plateau*/
				commentaireIntro(); 
				
				for (a=0; a<NBARMES; a++) {
					for (n=0; n<monde.stats[a].nombre; n++) {
						for (c=0; c<NBCOULEURS; c++) {

							printf("   Joueur %s, entrez les coordonées de votre %s %d/%d\n",couleursMots[c],armesMots[a], (n+1),monde.stats[a].nombre);

							tmpX = -1;
							tmpY = -1;
							entreeOk = false;
							
							do {
								lireCommande(&tmpX, &tmpY);

								entreeOk = estLibre(monde, tmpX, tmpY);					
								if (!entreeOk) {
									printf("   choisissez une case vide\n");
								}
							
							} while (!entreeOk);

							uniteTmp = creeUnite(couleursChar[c], a,tmpX,tmpY, monde.stats[a].vie);
							insereUnite(&monde.infosJoueurs[c], uniteTmp);
							poseUnite(&monde, uniteTmp, tmpX, tmpY);

								
							afficheMonde(monde, armesChar);
						}
					}
				}
				commentaireDebutBataille();
				etatDuJeu = 1;
				break;


			case(1): /*sélectionner une unité*/
				printf("     ============================\n       tour N°%d du joueur %s\n     ============================\n",monde.tour,couleursMots[idCouleurActive]);
				printf("   Joueur %s, choisissez une unité à déplacer.\n",couleursMots[idCouleurActive]);

				tmpX = -1;
				tmpY = -1;
				entreeOk = false;
				
				do {
					lireCommande(&tmpX, &tmpY);

					entreeOk = selectionnable(monde, couleurActive, tmpX, tmpY);
					
					if (!entreeOk) {
						printf("   choisissez une unité de votre couleur\n");
					}
				} while (!entreeOk);

				uniteJoueur = trouveUnite(monde, tmpX, tmpY);
				etatDuJeu = 2;
				break;

			case(2): /*déplacer l'unité*/
				creeAccessibilite(&monde, uniteJoueur->posX, uniteJoueur->posY, monde.stats[uniteJoueur->arme].endurance);
		
				afficheMonde(monde, armesChar);
		
				printf("   Joueur %s, déplacez votre unité en x:%d, y:%d vers une case libre\n",couleursMots[idCouleurActive], uniteJoueur->posX, uniteJoueur->posY);
				
				tmpX = -1;
				tmpY = -1;
				entreeOk = false;

				do {
					lireCommande(&tmpX, &tmpY);
					
					entreeOk = ((estLibre(monde, tmpX, tmpY) && monde.accessible[tmpX][tmpY]) || (tmpX == uniteJoueur->posX && tmpY == uniteJoueur->posY)); 
					
					if (!entreeOk) {
						printf("   choisissez une case libre et à votre portée\n");
					}
				} while (!entreeOk);

				deplaceUnite (&monde, uniteJoueur,tmpX, tmpY);
				videAccessibilite(&monde);

				etatDuJeu = 3;
				break;
			
			case(3):/*choisi une unité à attaquer*/

				creeAccessibilite(&monde, uniteJoueur->posX, uniteJoueur->posY, monde.stats[uniteJoueur->arme].portee);

				afficheMonde(monde, armesChar);
				printf("   Joueur %s, choisissez une case à attaquer avec votre unité en x:%d, y:%d\n",couleursMots[idCouleurActive], uniteJoueur->posX, uniteJoueur->posY);

				tmpX = -1;
				tmpY = -1;
				entreeOk = false;
				ptDegat = 0;

				do {
					lireCommande(&tmpX, &tmpY);
					
					entreeOk = (monde.accessible[tmpX][tmpY]); 
					
					if (!entreeOk) {
						printf("   choisissez une case à votre portée\n");
					}
				} while (!entreeOk);


				videAccessibilite(&monde);
				etatDuJeu = 4;
				break;

			case(4):/*blesse l'unité attaquée*/

				/*si le coup est donné dans le vide : il ne se passe rien*/
				if (estLibre(monde, tmpX, tmpY)) {
						afficheMonde(monde, armesChar);
						printf("   votre arme aterri dans la case x:%d, y:%d et se plante dans l'herbe\n", tmpX,tmpY);
				} else {
					/*blesse l'unité visée*/ 
					uniteCible = trouveUnite(monde, tmpX,tmpY);
			
					 if (estAlliee(uniteCible, uniteJoueur->couleur)) {
						ptDegat = 1;
						blesseUnite(&monde, uniteCible, ptDegat);
						afficheMonde(monde, armesChar);
						printf("   Par maladresse, vous ateignez un allié en x:%d, y:%d de votre arme,\n   et lui infligez %dpt de dégat\n", tmpX,tmpY, ptDegat);
				
					} else {
						ptDegat = monde.stats[uniteJoueur->arme].force;
						blesseUnite(&monde, uniteCible, ptDegat);

						afficheMonde(monde, armesChar);
						printf("   Votre arme s'abat sur l'ennemi en x:%d, y:%d, et lui inflige %dpt de dégat\n", tmpX,tmpY,ptDegat);
					}
					
					/*vérifie si l'unité visée est morte*/
					if (monde.plateau[tmpX][tmpY] == NULL) {
						printf("   L'unite en x:%d, y:%d meurt. RIP",tmpX,tmpY);
					}
				}

				etatDuJeu = 5;
				break;

			case(5):/*passe le tour à l'autre joeur*/
				
				if (couleurActive == ROUGE) {
					couleurActive = BLEU;
					idCouleurActive = IDBLEU;
				}	
				else {
					couleurActive = ROUGE;
					idCouleurActive = IDROUGE;
					monde.tour ++;
				}

				etatDuJeu = 1;
			break;

			default: 
				printf("! Le programme ne devrait pas pouvoir atteindre cet état\n");
			break;
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
	creeAccessibilite(&monde, tmpX,tmpY,4);
	afficheMonde(monde);
	*/
	return 0;
}