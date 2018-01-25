#include <stdio.h>
#include <stdlib.h>

#define MAX_LENGTH 16

int main() {

  char filename[MAX_LENGTH];
  printf("Entrez le nom du fichier :\n");
  scanf("%s", filename);
  FILE* inputStream = fopen(filename, "r");
  FILE* outputStream = fopen("resultat.csv", "w");
  printf("Entrez la première ligne à permuter :\n");
  int firstColumn = 0;
  scanf("%d", &firstColumn);
  printf("Entrez la deuxième ligne à permuter :\n");
  int secondColumn = 0;
  scanf("%d", &secondColumn);

  if(secondColumn == firstColumn) {
    return(0);
  }

  if(secondColumn < firstColumn) {
    int temp = firstColumn;
    firstColumn = secondColumn;
    secondColumn = temp;
  }

  int nb = 0;

  // TODO - Finish the exercice (:

  //For each line...
  int firstValue;
  while(nb < firstColumn) {
    while(fgetc(inputStream) != ";");
    fscanf("%d", &firstValue;)
  }
}
