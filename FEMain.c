#include "FEFunctions.h"
#include "FEStructures.h"

#include <stdio.h>
#include <stdlib.h>


int main () {
	Monde monde;
	initMonde(&monde);
	int i = 0;
	for (i=0; i<monde.stats.hache.nombre; i++) {
		insereUnite(&monde.rouge.unites,'H', 4, i);
		insereUnite(&monde.bleu.unites,'H', 8, i);	
	}
	afficheMonde(monde);
	return 0;
}