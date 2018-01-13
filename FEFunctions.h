#include "FEStructures.h"


int initMonde (Monde* monde);

int secuScanInt ();
int lireCommande (int* x, int* y);

int dist(int a, int b, int c, int d);
int creeAccessibilite (Monde* monde, int x, int y, int dist);
int videAccessibilite (Monde* monde);

int afficheDeuxChiffres (int x);
int afficheMonde (Monde monde);

Unite* creeUnite (int couleur, int arme, int x, int y, int vie);
int insereUnite (InfoJoueur* joueur, Unite* unite);
int afficheListe (InfoJoueur infoJoueur);
bool selectionnable (Monde monde, int couleur, int x, int y);
int supprimeUnite (Monde* monde, Unite* unite);
Unite* trouveUnite (Monde monde, int x, int y);
int leveUnite (Monde* monde, Unite* unite);
int poseUnite (Monde* monde, Unite* unite, int x, int y);
int deplaceUnite (Monde* monde, Unite* unite, int x, int y);
int blesseUnite (Monde* monde, Unite* unite, int degat);
bool estLibre (Monde monde, int x, int y);
bool estAlliee (Unite* unite, int couleur);

int commentaireIntro ();
int commentaireDebutBataille ();




/*fonctions obsolètes*/
int supprimeUniteDepuisMonde (Monde* monde, int x, int y);