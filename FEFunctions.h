#include "FEStructures.h"


int initMonde (Monde* monde);
int secuScanInt();
int lireCommande(int* x, int* y);
int dist(int a, int b, int c, int d);
int estAProximite(Monde* monde, int x, int y, int dist);
int afficheDeuxChiffres (int x);
int afficheMonde (Monde monde);
Unite* creeUnite(char couleur, char arme, int x, int y, int vie);
int insereUnite(InfoJoueur* joueur, Unite* unite);
int supprimeUnite(Monde* monde, Unite* unite);
Unite* trouveUnite(Monde monde, int x, int y);
int leveUnite (Monde* monde, Unite* unite);
int poseUnite (Monde* monde, Unite* unite, int x, int y);
int deplaceUnite (Monde* monde, Unite* unite, int x, int y);




/*fonctions obsolètes*/
int supprimeUniteDepuisMonde(Monde* monde, int x, int y);