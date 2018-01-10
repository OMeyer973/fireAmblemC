#include "FEFunctions.h"
#include "FEStructures.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


int main () {
	Monde monde;
	initMonde(&monde);
	int i = 0;
	int tmpX, tmpY;
	Unite* uniteTmp;


	for (i=0; i<monde.stats.hache.nombre; i++) {
		uniteTmp = creeUnite(ROUGE, HACHE,4,i, monde.stats.hache.vie);
		insereUnite(&monde.rouge, uniteTmp);
		monde.plateau[4][i] = uniteTmp;
	}
	afficheMonde(monde);

	uniteTmp = trouveUnite(monde,4,0);
	supprimeUnite(&monde,uniteTmp);
	afficheMonde(monde);
/*
	uniteTmp = trouveUnite(monde,4,1);
	deplaceUnite(&monde,uniteTmp,5,1);

	afficheMonde(monde);
	lireCommande(&tmpX, &tmpY);

	printf("tmpX : %d, tmpY : %d\n", tmpX, tmpY);
	estAProximite(&monde, tmpX,tmpY,4);
	afficheMonde(monde);
	*/
	return 0;
}