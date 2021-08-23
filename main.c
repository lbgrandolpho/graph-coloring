#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "leitura.h"
#include "coloracao.h"

int main(int argc, char **argv) {

    int algoritmo = 0, opt = 0, i, indice, dim, k;

    while (opt != -1) {
        opt = getopt(argc, argv, ":i:a:");  //pega as flags de parametro

        switch (opt) {
            case 'i':                  //arquivo de entrada
                indice = optind - 1;
                break;

            case 'a':               //algoritmo que se deseja utilizar
                algoritmo = atoi(argv[optind - 1]);
                break;
        }
    }

    int **mat = lerArquivo(argv[indice], &dim);

    switch (algoritmo) {
        case 1:
            k = solucaoOtima(mat, dim);
            printf("k = %d\n", k);
            break;

        case 2:
            k = heuristica1(mat, dim);
            printf("k = %d\n", k);
            break;

        case 3:
            k = heuristica2(mat, dim);
            printf("k = %d\n", k);
            break;

        default:
            printf("Algoritmo inexistente\n");
            break;
    }

    for (i=0; i < dim; i++)
        free(mat[i]);

    free(mat);

}
