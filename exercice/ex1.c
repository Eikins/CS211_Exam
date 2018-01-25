#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define LAST 100000

int cube(int n);

int matchesConsign(int n);

int main() {
  for(int i = 0; i <= LAST; i++) {
    if(matchesConsign(i)) {
      printf("%d\n", i);
    }
  }
  return 0;
}

int cube(int n) {
  return n * n * n;
}

int matchesConsign(int n) {
  int nb = 1;
  int nCopy = n;
  int sum = 0;
  // Récupération du nombre de chiffres
  while(n / (pow(10, nb)) != 0) {
    nb++;
  }
  for(int i = 1; i < nb; i++) {
      sum += cube(nCopy % (int)pow(10, i) / (int)pow(10, i - 1));
      nCopy -= nCopy % (i * 10);
  }
  return sum == n;
}
