#include "FEFunctions.h"
#include "FEStructures.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


int main () {

	Monde monde;
	
	Unite* uniteJoueur;
	Unite* uniteCible;

	
	int a = 0; /*int pour identifier les armes*/
	int n = 0; /*int pour identifier le nombre d'unités*/
	int c = 0; /*int pour identifier la couleur*/

	int tmpX, tmpY;
	bool entreeOk;

	int ptDegat;



	initMonde(&monde);

	afficheMonde(monde);
	while(monde.infoJeu.etatDuJeu != 10) {
		/* RAPPELS ETATS DU JEU :
		0 : placement des armées sur le plateau
		1 : sélectionner une unité
		2 : déplacer une unité
		3 : choisi une unité à attaquer
		4 : blesse l'unité attaquée
		5 : vérifie que le jeu ne soit pas fini
		6 : passe le tour à l'autre joueur
		10 : jeu fini (on sort du programme)
		*/

		switch(monde.infoJeu.etatDuJeu) {
			case(0): /*placement initial des unités sur le plateau*/
				commentaireIntro(); 
				
				Unite* uniteTmp;
			
				for (a=0; a<NBARMES; a++) {
					for (n=0; n<monde.stats[a].nombre; n++) {
						for (c=0; c<NBCOULEURS; c++) {

							printf("   Joueur %s, entrez les coordonées de votre %s %d/%d\n",monde.textes.couleursMots[c],monde.textes.armesMots[a], (n+1),monde.stats[a].nombre);

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

							uniteTmp = creeUnite(c, a,tmpX,tmpY, monde.stats[a].vie);
							insereUnite(&monde.infosJoueurs[c], uniteTmp);
							poseUnite(&monde, uniteTmp, tmpX, tmpY);

								
							afficheMonde(monde);
						}
					}
				}
				commentaireDebutBataille();
				monde.infoJeu.etatDuJeu = 1;
				break;


			case(1): /*sélectionner une unité*/
				printf("     ============================\n       Tour N°%d du joueur %s\n     ============================\n",monde.infoJeu.tour,monde.textes.couleursMots[monde.infoJeu.couleurActive]);
				printf("   Joueur %s, choisissez une unité à déplacer.\n",monde.textes.couleursMots[monde.infoJeu.couleurActive]);

				tmpX = -1;
				tmpY = -1;
				entreeOk = false;
				
				do {
					lireCommande(&tmpX, &tmpY);

					entreeOk = selectionnable(monde, monde.infoJeu.couleurActive, tmpX, tmpY);
					
					if (!entreeOk) {
						printf("   choisissez une unité de votre couleur\n");
					}
				} while (!entreeOk);

				uniteJoueur = trouveUnite(monde, tmpX, tmpY);
				monde.infoJeu.etatDuJeu = 2;
				break;

			case(2): /*déplacer l'unité*/
				creeAccessibilite(&monde, uniteJoueur->posX, uniteJoueur->posY, monde.stats[uniteJoueur->arme].endurance);
		
				afficheMonde(monde);
		
				printf("   Joueur %s, déplacez votre unité en x:%d, y:%d vers une case libre\n",monde.textes.couleursMots[monde.infoJeu.couleurActive], uniteJoueur->posX, uniteJoueur->posY);
				
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

				monde.infoJeu.etatDuJeu = 3;
				break;
			
			case(3):/*choisi une unité à attaquer*/

				creeAccessibilite(&monde, uniteJoueur->posX, uniteJoueur->posY, monde.stats[uniteJoueur->arme].portee);

				afficheMonde(monde);
				printf("   Joueur %s, choisissez une case à attaquer avec votre unité en x:%d, y:%d\n",monde.textes.couleursMots[monde.infoJeu.couleurActive], uniteJoueur->posX, uniteJoueur->posY);

				tmpX = -1;
				tmpY = -1;
				entreeOk = false;

				do {
					lireCommande(&tmpX, &tmpY);
					
					entreeOk = (monde.accessible[tmpX][tmpY]); 
					
					if (!entreeOk) {
						printf("   choisissez une case à votre portée\n");
					}
				} while (!entreeOk);


				videAccessibilite(&monde);
				monde.infoJeu.etatDuJeu = 4;
				break;

			case(4):/*blesse l'unité attaquée*/


				ptDegat = 0;


				/*si le coup est donné dans le vide : il ne se passe rien*/
				if (estLibre(monde, tmpX, tmpY)) {
						afficheMonde(monde);
						printf("   votre arme aterri dans la case x:%d, y:%d et se plante dans l'herbe\n", tmpX,tmpY);
				} else {
					/*blesse l'unité visée*/ 
					uniteCible = trouveUnite(monde, tmpX,tmpY);
			
					 if (estAlliee(uniteCible, uniteJoueur->couleur)) {
						ptDegat = 1;
						blesseUnite(&monde, uniteCible, ptDegat);
						afficheMonde(monde);
						printf("   Par maladresse, vous ateignez un allié en x:%d, y:%d de votre arme,\n   et lui infligez %dpt de dégat. Ouille\n", tmpX,tmpY, ptDegat);
				
					} else {
						ptDegat = monde.stats[uniteJoueur->arme].force;
						blesseUnite(&monde, uniteCible, ptDegat);

						afficheMonde(monde);
						printf("   Votre arme s'abat sur l'ennemi en x:%d, y:%d, et lui inflige %dpt de dégat\n", tmpX,tmpY,ptDegat);
					}
					
					/*vérifie si l'unité visée est morte*/
					if (monde.plateau[tmpX][tmpY] == NULL) {
						printf("   L'unite en x:%d, y:%d meurt. RIP\n",tmpX,tmpY);
						printf("   Il reste %d unites au joueur %s et %d unites au joueur %s\n",monde.infosJoueurs[IDROUGE].nbUnites, monde.textes.couleursMots[IDROUGE], monde.infosJoueurs[IDBLEU].nbUnites, monde.textes.couleursMots[IDBLEU]);
					}
				}

				monde.infoJeu.etatDuJeu = 5;
				break;

			case(5):/*vérifie que le jeu ne soit pas fini*/

				c = 0;

				for (c=0; c<NBCOULEURS; c++) {
					if (monde.infosJoueurs[c].nbUnites == 0) {
						printf("   L'armée du joueur %s est vaincue\n", monde.textes.couleursMots[c]);
						printf("     =========================================\n       Le joueur %s remporte la victoire !\n     =========================================\n",monde.textes.couleursMots[(c+1)%2]);
							monde.infoJeu.etatDuJeu = 10;
					}
				}
				
				if (monde.infoJeu.etatDuJeu != 10){
					monde.infoJeu.etatDuJeu = 6;
				}
				break;

			case(6):/*passe le tour à l'autre joeur*/
				if (monde.infoJeu.couleurActive == IDROUGE) {
					monde.infoJeu.couleurActive = IDBLEU;
				}	
				else {
					monde.infoJeu.couleurActive = IDROUGE;
					monde.infoJeu.tour ++;
				}

				monde.infoJeu.etatDuJeu = 1;
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