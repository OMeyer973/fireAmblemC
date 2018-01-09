#include "FEStructures.h"


int initMonde (Monde* monde);
int afficheDeuxChiffres (int x);
int afficheMonde (Monde monde);
Unite* creeUnite(char couleur, char arme, int x, int y, int vie);
int insereUnite(InfoJoueur* joueur, Unite* unite);
int supprimeUnite(Monde* monde, int x, int y);
Unite* trouveUnite(Monde monde, int x, int y);
int deplaceUnite (Monde* monde, Unite* unite, int x, int y);