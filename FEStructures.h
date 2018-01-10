#include <stdbool.h>

#ifndef STRUCTURES_H_INCLUDED
#define STRUCTURES_H_INCLUDED

/* dimension du monde en nombre de cases */
#define HAUT 12
#define LARG 18

#define ROUGE 'R' /*identifiant du premier joueur*/
#define BLEU 'B' /*identifiant du deuxi`eme joueur*/

/* les armes des unités*/
#define HACHE 'H'
#define LANCE 'L'
#define EPEE 'E'
#define ARC 'A'

typedef struct ustat{ /*structure contenant les statistiques d'une unitée donnée*/
	int nombre; /*nombre d'unités de ce type dans les armées*/
	int endurance; /*endurance de l'unité (nb de cases qu'elle peut parcourir en 1 tour)*/
	int portee; /*distance à laquelle l'unité peut attaquer*/
	int vie; /*points de vie de l'unité*/
	int force; /*dommages que l'unité inflige en attaquant*/
} Ustat;

typedef struct stats{/*structure contenant les statistiques de tous les types d'unités*/
	Ustat hache;
	Ustat lance;
	Ustat epee;
	Ustat arc;
} Stats;

typedef struct unite{ /*infos sur une unité dans l'armée d'un joueur*/
	char couleur; /*R ou B pour ROUGE ou BLEU*/
	char arme; /*H L E ou A pour hache, lance, épée, arc*/
	struct unite *suiv; /*liste des unités suivantes*/
	int posX, posY; /*pour stocker les coordonnées de l'unité*/
	int vie; /*nombre de points de vie de l'unité*/
} Unite;

typedef struct infoJoueur { /*donne des infos sur l'armée du joueur*/
	int nbUnites; /*nombre d'unités du joueur*/
	Unite* unites; /*liste des unités du joueur*/
}InfoJoueur;

typedef struct monde{ /*contient toutes les infos relatives à la partie en cours*/
	Unite* plateau[HAUT][LARG];
	bool accessible[HAUT][LARG]; /*tableau donnant des renseignement sur la proximité de certaines cases par rapport à l'unité jouant*/
	int tour; /* Numero du tour */
	Stats stats; /*statistiques concernant les types d'unités du jeu*/
	InfoJoueur rouge, bleu; /*Listes des unités des deux joueurs*/
} Monde;


#endif /* STRUCTURES_H_INCLUDED */