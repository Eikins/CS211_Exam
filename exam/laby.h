#define MUR -2
#define	VIDE -1
#define FOOT -3

struct labyrinthe {
	short int (**laby);
	int maxX;
	int maxY;
};

struct deplacement {
	int x;
	int y;
	struct deplacement *next;
};


// recupere et retourne un nombre entrer au clavier.
int labyEntrer();

// Alloue le champ laby de la structure labyrinthe.
// retourne 1 si toutes les allocations se sont faites correctement, 0 sinon.
int labyAllouer(struct labyrinthe *l);

// Initialise le champ laby de la structure labyrinthe, une fois que ce champ a été alloué.
// Initialise les cases de manières aléatoire en fonction de la probabilité d'avoir un MUR.
// des vérifications supplémentaires pourront être faite.
void labyCreer(struct labyrinthe l,float pourcentage);

// Affiche un labyrinthe
void labyAfficher(struct labyrinthe l);

// Realise la première phase de l'algorithme
// En partant de la case départ, modifie les cases atteignables (pas un MUR) avec leur distance (en pas) à l'entrée.
// retourne par convention 0 si la sortie n'est pas atteinte.
// retourne le nombre d'iterations necessaire sinon.
int labyEtendre(struct labyrinthe l);

// Empile (donc modifie le haut de la pile.) les coordonnées la case dans la structure deplacement (attention au type du premier élément.)
int labyEmpiler(struct deplacement **p,int x,int y);

// Depile un élément de la structure (donc modifie le haut de la pile.)
struct deplacement *labyDepiler(struct deplacement **p);

// Utilise le labyrinthe rempli par la partie 1
// Trouve un chemin en partant de la sortie afin de remplir l'ensemble C (empiler dans la liste chainée pile déclarée en global)
void labyTrouverChemin(struct labyrinthe l,int iteration);

// Permet de savoir si tout le labyrinthe a été analysé lors de la phase d'expansion.
int isFullyDiscovered(struct labyrinthe l);

//Enlève les markeurs posés lors de la phase d'epansion
void removeLabyMarkers(struct labyrinthe l);

//Affiche le chemin trouvé;
void printPath(struct labyrinthe l, int playAnimation);

//Pause le programme pendant le temps donné en secondes
void wait(int second);
