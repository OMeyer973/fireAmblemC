#include "FEFunctions.h"
#include "FEStructures.h"

#include <stdio.h>
#include <stdlib.h>


int main () {
	Monde monde;
	initMonde(&monde);
	int i = 0;
	Unite* uniteTmp;
	for (i=0; i<monde.stats.hache.nombre; i++) {
		uniteTmp = creeUnite('R','H',4,i, monde.stats.hache.vie);
		insereUnite(&monde.rouge, uniteTmp);
		monde.plateau[4][i] = uniteTmp;
	}
	afficheMonde(monde);

	supprimeUnite(&monde,4,2);
	afficheMonde(monde);

	uniteTmp = trouveUnite(monde,4,1);
	deplaceUnite(&monde,uniteTmp,5,1);

	afficheMonde(monde);
	return 0;
}