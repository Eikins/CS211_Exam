#include <time.h>
#include "laby.h"
#include <stdlib.h>
#include <stdio.h>

struct deplacement *pile=NULL;

// recupere et retourne un nombre entrer au clavier.
int labyEntrer()
{
	int value = -1;
	scanf("%d", &value);
	return value;
}

// Alloue le champ laby de la structure labyrinthe.
// retourne 1 si toutes les allocations se sont faites correctement, 0 sinon.
int labyAllouer(struct labyrinthe *l)
{
	l->laby = malloc(sizeof(void*) * l->maxY);
	if(l->laby == NULL) {
		return 0;
	}
	for(int i = 0; i < l->maxY; i++) {
		l->laby[i] = malloc(sizeof(short int) * l->maxX);
		if(l->laby[i] == NULL) {
			return 0;
		}
	}
	return 1;
}

// Initialise le champ laby de la structure labyrinthe, une fois que ce champ a été alloué.
// Initialise les cases de manières aléatoire en fonction de la probabilité d'avoir un MUR.
// des vérifications supplémentaires pourront être faite.
void labyCreer(struct labyrinthe l,float pourcentage)
{
	int i,j;
	srand(time(NULL));
	for (i=0;i<l.maxY;i++) {
		for (j=0;j<l.maxX;j++) {
			if ((pourcentage*100)<(rand()%100)) {
				l.laby[i][j]=VIDE;
			} else {
				l.laby[i][j]=MUR;
			}
		}
	}
	l.laby[0][0]=VIDE;
	l.laby[l.maxY-1][l.maxX-1]=VIDE;
}
// Affiche un labyrinthe (MUR ou VIDE)
void labyAfficher(struct labyrinthe l)
{
	printf("|");
	for(int i = 0; i < l.maxX; i++) {
		printf("=");
	}
	printf("|\n");
	for (int i = 0; i < l.maxY; i++) {
		printf("|");
		for(int j = 0; j < l.maxX; j++) {
			if(l.laby[i][j] == VIDE) {
				printf(" ");
			} else if(l.laby[i][j] == MUR){
				printf("#");
			} else if(l.laby[i][j] == FOOT){
				printf("X");
			}
			//DEBUG
			else {
				printf("%d", l.laby[i][j]);
			}
		}
		printf("|\n");
	}
	printf("|");
	for(int i = 0; i < l.maxX; i++) {
		printf("=");
	}
	printf("|\n");
}

// Realise la première phase de l'algorithme
// En partant de la case départ, modifie les cases atteignables (pas un MUR) avec leur distance (en pas) à l'entrée.
// retourne par convention 0 si la sortie n'est pas atteinte.
// retourne le nombre d'iterations necessaire sinon.
int labyEtendre(struct labyrinthe l)
{
	int iteration = 0;
	l.laby[0][0] = 0;
	int flag = 1;
	// Tant qu'on a trouvé au moins un passage vers une prochaine étape ou que le laby n'a pas été entièrement analysé.
	while(flag && !isFullyDiscovered(l)) {
		flag = 0;
		for(int i = 0; i < l.maxY; i++) {
			for(int j = 0; j < l.maxX; j++) {
				if(l.laby[i][j] == iteration) {
					// Pour chaque case de Psi...
					for(int vi = -1; vi <= 1; vi++) {
						for(int vj = -1; vj <= 1; vj++) {
							// On vérifie que les cases autours appartiennent bien au labyrinthe
							if(vj != vi && vj != -vi && i + vi >= 0 && i + vi < l.maxY && j + vj >= 0 && j + vj < l.maxX) {
								// Pour chaque voisin...
								if(l.laby[i + vi][j + vj] == VIDE) {
									l.laby[i + vi][j + vj] = iteration + 1;
									// On a trouvé au moins 1 passage.
									flag = 1;
								}
							}
						}
					}
				}

			}
		}
		iteration = iteration + 1;
	}
	return flag ? iteration : 0;
}

int isFullyDiscovered(struct labyrinthe l) {
	for(int i = 0; i < l.maxY; i++) {
		for(int j = 0; j < l.maxX; j++) {
			if(l.laby[i][j] == VIDE) {
				return 0;
			}
		}
	}
	return 1;
}

// Empile (donc modifie le haut de la pile.) les coordonnées la case dans la structure deplacement (attention au type du premier élément.)
int labyEmpiler(struct deplacement **p,int x,int y)
{
	struct deplacement* newHead = malloc(sizeof(struct deplacement));
	if(newHead == NULL) {
		return 0;
	}
	newHead->x = x;
	newHead->y = y;
	newHead->next = *p;
	*p = newHead;
	return 1;
}

// Depile un élément de la structure (donc modifie le haut de la pile.)
struct deplacement *labyDepiler(struct deplacement **p)
{
	struct deplacement* head = *p;
	*p = head->next;
	return head;
}


// Utilise le labyrinthe rempli par la partie 1
// Trouve un chemin en partant de la sortie afin de remplir l'ensemble C (empiler dans la liste chainée pile déclarée en global)
void labyTrouverChemin(struct labyrinthe l,int iteration)
{
	int iterationCopy = iteration;
	labyEmpiler(&pile, l.maxX - 1, l.maxY - 1);
	while(pile->x != 0 || pile->y != 0) {
		for(int vi = -1; vi <= 1; vi++) {
			for(int vj = -1; vj <= 1; vj++) {
				// On vérifie que les cases autours appartiennent bien au labyrinthe
				if(vj != vi && vj != -vi && pile->y + vi >= 0 && pile->y + vi < l.maxY && pile->x + vj >= 0 && pile->x + vj < l.maxX) {
					// Pour chaque voisin...
					if(l.laby[pile->y + vi][pile->x + vj] == iterationCopy - 1) {
						labyEmpiler(&pile, pile->x + vj, pile->y + vi);
					}
				}
			}
		}
		iterationCopy = iterationCopy - 1;
	}
}

void removeLabyMarkers(struct labyrinthe l) {
	for(int i = 0; i < l.maxY; i++) {
		for(int j = 0; j < l.maxX; j++) {
			if(l.laby[i][j] >= 0) {
				l.laby[i][j] = VIDE;
			}
		}
	}
}

void printPath(struct labyrinthe l, int playAnimation) {
	while(pile != NULL) {
		struct deplacement* move = labyDepiler(&pile);
		l.laby[move->y][move->x] = FOOT;
		free(move);
		// Tried to overwrite last print in the terminal, didn't work.
		//fseek(stdout, -((l.maxX) * (l.maxY + 1)) - 1, SEEK_CUR);
		if(playAnimation) {
			labyAfficher(l);
			wait(1);
		}
	}
	labyAfficher(l);
}

void wait(int second) {
	long t = time(NULL);
	while(time(NULL) - t < second);
}
