#ifndef STRUCTURES_H_INCLUDED
#define STRUCTURES_H_INCLUDED


/* dimension du monde en nombre de cases */
#define HAUT 12
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
	Unite *plateau[HAUT][LARG];
	int tour; /* Numero du tour */
	UListe rouge, bleu; /*Listes des deux joueurs*/
} Monde;


#endif /* STRUCTURES_H_INCLUDED */