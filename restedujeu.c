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