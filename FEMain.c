#include "FEFunctions.h"
#include "FEStructures.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <MLV/MLV_all.h>
#include <unistd.h>


int main () {

	Monde monde;
	
	Unite* uniteJoueur;
	Unite* uniteCible;
	Unite* uniteTmp;
	char* texteInfos;

	
	int a = 0; /*int pour identifier les armes*/
	int n = 0; /*int pour identifier le nombre d'unités*/
	int c = 0; /*int pour identifier la couleur*/

	int tmpX, tmpY;
	bool entreeOk;

	int ptDegat;

	MLV_Keyboard_button sym;
	MLV_Keyboard_modifier mod;
	int unicode, mouse_x, mouse_y;

	initMonde(&monde);


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
				
				dessinePlateau(monde);
				for (a=0; a<NBARMES; a++) { 
					for (n=0; n<monde.stats[a].nombre; n++) {
						for (c=0; c<NBCOULEURS; c++) {
							
							tmpX = -1;
							tmpY = -1;

							/* On affiche les infos dans l'UI */
							reinitialiseInfos(monde, c, 0);
							prepareInfosIntro(&monde, c, a);

							MLV_wait_keyboard_or_mouse( &sym, &mod, &unicode, &mouse_x, &mouse_y );
							do{ /* On attend un clic et on vérifie s'il est valide (case du plateau vide) */
								entreeOk = verifClicValide(&tmpX, &tmpY) && estLibre(monde, tmpX, tmpY);
								if (!entreeOk) {
									texteInfos = "Choisissez une case vide et valide\n";
									reinitialiseInfos(monde, c, 0);
									afficheInfos(texteInfos); /* On affiche un message si ce n'est pas le cas */
									MLV_wait_keyboard_or_mouse( &sym, &mod, &unicode, &mouse_x, &mouse_y );
								}
							} while (!entreeOk);

							/* S'il l'est, on ajoute l'unité et on la dessine */
							uniteTmp = creeUnite(c, a, tmpX,tmpY, monde.stats[a].vie);
							insereUnite(&monde.infosJoueurs[c], uniteTmp);
							poseUnite(&monde, uniteTmp, tmpX, tmpY);
							actualiseJeu(&monde);
			
						}
					}
				}
				monde.infoJeu.etatDuJeu = 1;
			break;

			case(1): /*sélectionner une unité*/
				tmpX = -1;
				tmpY = -1;

				/* On affiche les informations de la phase en cours dans l'UI */
				actualiseJeu(&monde);
				reinitialiseInfos(monde, monde.infoJeu.couleurActive, 1);
				texteInfos = "Choisissez une unité à déplacer.\n";
				afficheInfos(texteInfos);

				MLV_wait_keyboard_or_mouse( &sym, &mod, &unicode, &mouse_x, &mouse_y );
				do{ /* On attend un clic et on vérifie s'il est valide (clique sur une unité du joueur actif) */
					entreeOk = verifClicValide(&tmpX, &tmpY) && selectionnable(monde, monde.infoJeu.couleurActive, tmpX, tmpY);
					if (!entreeOk) {
						texteInfos = "Veuillez choisir une unité valide\n";
						reinitialiseInfos(monde, monde.infoJeu.couleurActive, 1);
						afficheInfos(texteInfos); /* On affiche un message si ce n'est pas le cas */
						MLV_wait_keyboard_or_mouse( &sym, &mod, &unicode, &mouse_x, &mouse_y );
					}

				} while (!entreeOk);

				/* S'il l'est, on met l'unité dans une variable de type Unite* pour l'utiliser par la suite */
				uniteJoueur = trouveUnite(monde, tmpX, tmpY);


				monde.infoJeu.etatDuJeu = 2;
			break;

			case(2): /*déplacer l'unité*/

				/* On modifie les informations dans l'UI + on dessine le rayon de déplacement possible de l'unité sélectionnée */
				reinitialiseInfos(monde, monde.infoJeu.couleurActive, 2);
				dessineAccessibilite(&monde, uniteJoueur->posX, uniteJoueur->posY, monde.stats[uniteJoueur->arme].endurance);

				tmpX = -1;
				tmpY = -1;

				MLV_wait_keyboard_or_mouse( &sym, &mod, &unicode, &mouse_x, &mouse_y );
				do{ /* On attend un clic et on vérifie s'il est valide (case à portée et vide) */
					entreeOk = (verifClicValide(&tmpX, &tmpY) && monde.accessible[tmpX][tmpY]);
					if (!entreeOk) {
						texteInfos = "Choisissez une case vide et valide\n";
						reinitialiseInfos(monde, monde.infoJeu.couleurActive, 2);
						afficheInfos(texteInfos); /* On affiche un message si ce n'est pas le cas */
						MLV_wait_keyboard_or_mouse( &sym, &mod, &unicode, &mouse_x, &mouse_y );
					}

				} while (!entreeOk);

				/* S'il l'est, on deplace l'unité, on vide le tableau d'accessibilité et on actualise le jeu */
				leveUnite (&monde, uniteJoueur);
				poseUnite (&monde, uniteJoueur, tmpX, tmpY);
				videAccessibilite(&monde);
				actualiseJeu(&monde);
				monde.infoJeu.etatDuJeu = 3;
			break;
		

			case(3):/*choisi une unité à attaquer*/

				/* On vérifie s'il y a des unités ennemies à portée. Si c'est le cas, on peut attaquer. Sinon le tour passe directement */
				if(dessineAccessibiliteAttaque(&monde, uniteJoueur->posX, uniteJoueur->posY, monde.stats[uniteJoueur->arme].portee, uniteJoueur->couleur) != 0){
					dessineAccessibiliteAttaque(&monde, uniteJoueur->posX, uniteJoueur->posY, monde.stats[uniteJoueur->arme].portee, uniteJoueur->couleur);
					
					tmpX = -1;
					tmpY = -1;

					/* On modifie les infos dans l'UI */
					reinitialiseInfos(monde, monde.infoJeu.couleurActive, 3);
					texteInfos = "Choisissez une cible à attaquer.\nCliquez sur votre unité pour ne rien faire.";
					afficheInfos(texteInfos);

					MLV_wait_keyboard_or_mouse( &sym, &mod, &unicode, &mouse_x, &mouse_y );
					do{ /* On attend un clic et on vérifie s'il est valide (selection d'un ennemie à portée) */
						entreeOk = verifClicValide(&tmpX, &tmpY) && monde.accessible[tmpX][tmpY];
						if (!entreeOk) {
							texteInfos = "Choisissez une case valide\n";
							reinitialiseInfos(monde, monde.infoJeu.couleurActive, 3);
							afficheInfos(texteInfos); /* On affiche un message si ce n'est pas le cas */
							MLV_wait_keyboard_or_mouse( &sym, &mod, &unicode, &mouse_x, &mouse_y );
						}
					} while (!entreeOk);

					actualiseJeu(&monde);
					monde.infoJeu.etatDuJeu = 4;
				}
				else {
					monde.infoJeu.etatDuJeu = 5;
				}
				endorsUnite(&monde, uniteJoueur);
			break;	

			case(4):/*blesse l'unité attaquée*/
				uniteCible = trouveUnite(monde, tmpX,tmpY);
				if( (uniteCible->posX == uniteJoueur->posX) && (uniteCible->posY == uniteJoueur->posY) ){
					/*ne fait rien si le joueur clique sur son unité*/
					monde.infoJeu.etatDuJeu = 5;
				}
				else {
					/* On calcule les points de dégâts, on les affiche et on les applique sur l'unité ciblée */
					ptDegat = monde.stats[uniteJoueur->arme].force;
					if( (uniteCible->arme < 3) && ( uniteCible->arme == ((uniteJoueur->arme+1)%3)) ){
						ptDegat = ptDegat * 2;
					}

					affichageDegat(tmpX,tmpY, ptDegat);
					blesseUnite(&monde, uniteCible, ptDegat);

					if (monde.plateau[tmpX][tmpY] == NULL) {
						/*si l'untée blessée meurt, les informations affichées dans l'UI ne sont pas les mêmes*/
						actualiseJeu(&monde);
						reinitialiseInfos(monde, monde.infoJeu.couleurActive, 3);
						prepareInfosResultAttaque(&monde, ptDegat, 0);

						/* Les informations sont plus longues. On rajoute de la pause pour que l'utilisateur puisse lire */
						sleep(2);
					}
					else{
						reinitialiseInfos(monde, monde.infoJeu.couleurActive, 3);
						prepareInfosResultAttaque(&monde, ptDegat, 1);
					}
					sleep(2); /* Permet à l'utilisateur d'avoir le temps de lire avant le tour suivant qui réactualise l'UI */
				}
				monde.infoJeu.etatDuJeu = 5;
			break;

			case(5): /*vérifie que le jeu ou le tour ne soient pas finis */
				c = 0;
				for (c=0; c<NBCOULEURS; c++) {
					if (monde.infosJoueurs[c].nbUnites == 0) {
						reinitialiseInfos(monde, monde.infoJeu.couleurActive, 3);
						prepareInfosFinPartie((char*)monde.textes.couleursMots[c], (char *)monde.textes.couleursMots[(c+1)%2]); /* On affiche un message si ce n'est pas le cas */
						sleep(5);
						monde.infoJeu.etatDuJeu = 10;
					}
				}
				if (monde.infoJeu.etatDuJeu != 10) {
					if (monde.infosJoueurs[monde.infoJeu.couleurActive].nbUnites > monde.infosJoueurs[monde.infoJeu.couleurActive].nbEndormis) {
					/*Si toutes les unités ne sont pas endormies, on passe à l'étape suivante*/
					monde.infoJeu.etatDuJeu = 1;
				} else {
					monde.infoJeu.etatDuJeu = 6;
				}
				}
			break;

			case(6):/*passe le tour à l'autre joeur*/
				reveilleUnites(&monde, monde.infoJeu.couleurActive);
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
	videMonde(&monde);
	MLV_free_window();
	return 0;
}

