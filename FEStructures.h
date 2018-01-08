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
#define ARC ’A’

/*structure contenant les statistiques d'une unitée donnée*/
typedef struct ustat{
	int nombre; /*nombre d'unités de ce type dans les armées*/
	int endurance; /*endurance de l'unité (nb de cases qu'elle peut parcourir en 1 tour)*/
	int portee; /*distance à laquelle l'unité peut attaquer*/
	int vie; /*points de vie de l'unité*/
	int force; /*dommages que l'unité inflige en attaquant*/
} Ustat;

/*structure contenant les statistiques de tous les types d'unités*/
typedef struct stats{
	Ustat hache;
	Ustat lance;
	Ustat epee;
	Ustat arc;
} Stats;

typedef struct unite{
	int posX, posY; /*pour stocker les coordonnées de l’unité*/
	char couleur; /*R ou B pour ROUGE ou BLEU*/
	char arme; /*H L E ou A pour hache, lance, épée, arc*/
	struct unite *suiv; /*liste des unités suivantes*/
} Unite;

typedef struct infoJoueur {
	int nbUnites;
	Unite* unites;
}InfoJoueur;

typedef struct monde{
	Unite* plateau[HAUT][LARG];
	int tour; /* Numero du tour */
	Stats stats; /*statistiques concernant les types d'unités du jeu*/
	int nbRouges; /*nombre d'unités rouges sur le plateau*/
	int nbBleus; /*nombre d'unités bleues sur le plateau*/
	InfoJoueur rouge, bleu; /*Listes des unités des deux joueurs*/
} Monde;


#endif /* STRUCTURES_H_INCLUDED */