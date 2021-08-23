#ifndef COLORACAO
#define COLORACAO
#include <stdbool.h>

int solucaoOtima(int **mat, int dim);

bool kColoracao(int **mat, int dim, int *cores, int i, int k);

bool verificaCor(int **mat, int dim, int *cores, int i, int cor);

int heuristica1(int **mat, int dim);

int heuristica2(int **mat, int dim);

void selectionSort(int **v, int n);

#endif
