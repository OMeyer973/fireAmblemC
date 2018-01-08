#include "FEStructures.h"


int initMonde (Monde* monde);
int afficheMonde (Monde monde);
Unite* creeUnite(char couleur, char arme, int x, int y, int vie);
int insereUnite(InfoJoueur* joueur, Unite* unite);
int supprimeUnite(Monde* monde, int x, int y);