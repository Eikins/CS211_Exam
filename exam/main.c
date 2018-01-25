#include "laby.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc,char *argv[])
{
	struct labyrinthe l;
	// Entrez les dimensions du labyrinthe.
	printf("Entrer X\n");
	l.maxX=labyEntrer();
	printf("Entrer Y\n");
	l.maxY=labyEntrer();

	printf("X : %d\n", l.maxX);
	printf("Y : %d\n", l.maxY);
	// Allouez le labyrinthe
	labyAllouer(&l);
	// Creer le labyrinthe
	labyCreer(l, 0.1);
	// Afficher le labyrinthe
	labyAfficher(l);
	// Trouver le chemin
	int iteration = labyEtendre(l);
	if(iteration != 0) {
		labyTrouverChemin(l, iteration);
	}
	removeLabyMarkers(l);
	// Set second param to 0 if u wanna skip the animation
	printPath(l, 1);
}
