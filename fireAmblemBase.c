#include <stdio.h>
#include <stdlib.h>

/* dimension du monde en nombre de cases */
#define LONG 12
#define LARG 18

#define ROUGE ’R’ //identifiant du premier joueur
#define BLEU ’B’ //identifiant du deuxi`eme joueur

/* les armes des unités*/
#define HACHE ’H’
#define LANCE ’L’
#define EPEE ’E’
#define arc ’A’

typedef struct unite{
	int posX, posY; /*pour stocker les coordonnées de l’unité*/
	char couleur; /*R ou B pour ROUGE ou BLEU*/
	char arme; /*H L E ou A pour hache, lance, épée, arc*/
	struct unite *suiv; /*liste des unités suivantes*/
} Unite;

typedef Unite* UListe;

typedef struct monde{
	Unite *plateau[LONG][LARG];
	int tour; /* Numero du tour */
	UListe rouge, bleu; /*Listes des deux joueurs*/
} Monde;



int main () {

	return 0;
}