#include <stdio.h>
#include <stdlib.h>
#include "leitura.h"

int **lerArquivo (char *txt, int *dim) {   //função que lê o grafo

    FILE *arq = fopen(txt, "r");

    if (arq == NULL)   //caso ocorra algum erro
        return NULL;

    int i, j, u=-1, v=-1;
    fscanf(arq, "%d", dim);   //lê a dimensão

    int **mat = (int**)malloc(sizeof(int*) * (*dim)); //aloca matriz de adjacencia
    for (i=0; i < *dim; i++) {
        mat[i] = (int*)malloc(sizeof(int) * (*dim));
        for (j=0; j < *dim; j++)
            mat[i][j] = 0;
    }

    while (!feof(arq)) {   //lê as arestas
        fscanf(arq, "%d%d", &u, &v);
        if (u != -1 && v != -1) {
            mat[u][v] = 1;
            mat[v][u] = 1;
        }
    }

    fclose(arq);   //fecha o arquivo

    return mat;    //retorna a matriz
}
