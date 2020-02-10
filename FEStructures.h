#include <stdbool.h>

#ifndef STRUCTURES_H_INCLUDED
#define STRUCTURES_H_INCLUDED

/* dimension du monde en nombre de cases */
#define HAUT 12
#define LARG 18
#define pixelsParCase 50

#define ROUGE 'R' /*identifiant du premier joueur*/
#define BLEU 'B' /*identifiant du deuxi`eme joueur*/

/*les ID des 2 couleurs dans le monde*/
#define NBCOULEURS 2
#define IDROUGE 0
#define IDBLEU 1

/* les armes des unités*/
#define HACHE 'H'
#define LANCE 'L'
#define EPEE 'E'
#define ARC 'A'

/*les id des armes dans les stats*/
#define NBARMES 4
#define IDHACHE 0
#define IDLANCE 1
#define IDEPEE 2
#define IDARC 3

typedef struct ustat{ /*structure contenant les statistiques d'une unitée donnée*/
	int nombre; /*nombre d'unités de ce type dans les armées*/
	int endurance; /*endurance de l'unité (nb de cases qu'elle peut parcourir en 1 tour)*/
	int portee; /*distance à laquelle l'unité peut attaquer*/
	int vie; /*points de vie de l'unité*/
	int force; /*dommages que l'unité inflige en attaquant*/
} Ustat;

typedef struct unite{ /*infos sur une unité dans l'armée d'un joueur*/
	int couleur; /*R ou B pour ROUGE ou BLEU*/
	int arme; /*0 1 2 3 pour hache, lance, épée, arc*/
	struct unite* suiv; /*liste des unités suivantes*/
	int posX, posY; /*pour stocker les coordonnées de l'unité*/
	int vie; /*nombre de points de vie de l'unité*/
	bool dort; /*renseigne si l'unité dort ou a fini son tour*/
} Unite;

typedef Unite* UListe;

typedef struct infoJoueur { /*donne des infos sur l'armée du joueur*/
	int nbUnites; /*nombre d'unités du joueur*/
	int nbEndormis;
	UListe unites; /*liste chaînée des unités du joueur*/
}InfoJoueur;

typedef struct infoJeu { /*des informations sur le déroulement de la partie en cours*/
	int tour; /* Numero du tour */
	int etatDuJeu;
	int couleurActive;
	Unite* uniteJoueur;
	Unite* uniteCible;
} InfoJeu;

typedef struct textes {
	/*string des charactères des couleurs et des armes,
	pour pouvoir les obtenir grâce à in id numérique*/
	const char *couleursChar;
	const char *armesChar;

	/*tableau de string des mots des couleurs et des armes 
	pour écrire des commentaires à partir des ID*/
	const char *couleursMots[NBCOULEURS];
	const char *armesMots[NBARMES];

	/* tableau des chemins des sprites des unités */
	char* tab_chemin_rouge[NBARMES];
	char* tab_chemin_bleu[NBARMES];

	/* tableau des chemins de l'image de fond de plateau et de l'UI + l'image renseignant le joueur actif*/
	char* chemin_plateau;
	char* chemin_infos;
	char* tab_chemin_joueurActif[NBCOULEURS];

	/* tableau des chemins vers les images qui indiquent les phases */
	char* tab_chemin_phase[4];

} Textes;

typedef struct monde{ /*contient toutes les infos relatives à la partie en cours*/
	Unite* plateau[HAUT][LARG];
	bool accessible[HAUT][LARG]; /*tableau donnant des renseignement sur la proximité de certaines cases par rapport à l'unité jouant*/
	Ustat stats[4]; /*statistiques concernant les types d'unités du jeu*/
	InfoJoueur infosJoueurs[2]; /*Listes des unités des deux joueurs*/
	InfoJeu infoJeu;
	Textes textes;
} Monde;


#endif /* STRUCTURES_H_INCLUDED */