#include "FEStructures.h"


int initMonde (Monde* monde);


int dist(int a, int b, int c, int d);
int creeAccessibilite (Monde* monde, int x, int y, int dist);
int videAccessibilite (Monde* monde);

Unite* creeUnite (int couleur, int arme, int x, int y, int vie);
int insereUnite (InfoJoueur* joueur, Unite* unite);
int supprimeUnite (Monde* monde, Unite* unite);
Unite* trouveUnite (Monde monde, int x, int y);
int leveUnite (Monde* monde, Unite* unite);
int poseUnite (Monde* monde, Unite* unite, int x, int y);
int deplaceUnite (Monde* monde, Unite* unite, int x, int y);
int blesseUnite (Monde* monde, Unite* unite, int degat);
bool estLibre (Monde monde, int x, int y);

int dessinePlateau();
int actualiseJeu(Monde* monde);
int reinitialiseInfos(Monde monde, int idJoueurActif, int phaseActuelle);
int prepareInfosIntro(Monde* monde, int couleurActive, int armesActive);
int prepareInfosResultAttaque(Monde* monde, int ptDegat, int valeurCase);
int afficheInfos(char* texte);
int afficheJoueurActif(char* couleur);
int prepareInfosFinPartie(char* perdant, char* gagnant);
bool verifClicValide(int* posX, int* posY);
int dessineUnite(Monde monde, int couleur,int idarme, int x, int y, int vie);
int dessineBarreVie(Monde* monde, Unite unite);
bool selectionnable(Monde monde, int couleur, int x, int y);
int dessineAccessibilite(Monde* monde, int x, int y, int maxDist);
int dessineAccessibiliteAttaque(Monde* monde, int x, int y, int couleur, int maxDist);
bool verifSelectionAttaque(Monde* monde,int x, int y, Unite* uniteJoueur);
int affichageDegat(int x, int y, int ptDegat);
int endorsUnite(Monde* monde, Unite* unite);
int reveilleUnites(Monde* monde, int couleur);
int videMonde(Monde* monde);