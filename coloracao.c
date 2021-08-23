#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "coloracao.h"


/* O algoritmo para encontrar a solução ótima implementado utiliza uma técnica
de backtracking. A função kColorocao verifica de forma recursiva se é possível
colorir o grafo dado para k cores, usando a função verificaCor que retorna se
o vértice pode receber aquela cor ou não. Esse k irá variar de 1 até o número
de vértices. Ao encontrar uma resposta válida para k, esse valor será retornado.
*/

// Baseado em https://www.geeksforgeeks.org/m-coloring-problem-backtracking-5/

int solucaoOtima(int **mat, int dim) {

    int *cores = (int*)malloc(sizeof(int)*dim);
    //cada posição representa a cor de cada vértice
    int k=0, j;

    do {
        for (j=0; j<dim; j++)
            cores[j] = 0;
        k++;
    } while (!kColoracao(mat, dim, cores, 0, k));

    free(cores);

    return k;
}

bool kColoracao(int **mat, int dim, int *cores, int i, int k) {

    int cor_atual;

    if (i == dim)  //condição de parada
        return true;

    for (cor_atual=1; cor_atual <= k; cor_atual++) {
        if (verificaCor(mat, dim, cores, i, cor_atual)) {
            cores[i] = cor_atual;
            if(kColoracao(mat, dim, cores, i+1, k))
                return true;
            cores[i] = 0;
        }
    }
    return false;    //poda do backtracking
}

bool verificaCor(int **mat, int dim, int *cores, int i, int cor) {

    int j;

    for(j=0; j<dim; j++)
        if(mat[i][j] && cor == cores[j])
            return false;   //testa se existe vértices adjacentes com a mesma cor

    return true; //se não retornou falso nenhuma vez, então não há vértices
                 //adjacentes com a mesma cor, e essa cor pode ser usada

}


//Algoritmo de ordenação que será usado na heurística de Welsh-Powell
void selectionSort(int **v, int n) {

    int i, j, menor, troca;

    for (i = 0; i < n-1; i++) {
        menor = i;
        for (j = i+1; j < n; j++)
            if (v[2][j] < v[2][menor])
                menor = j;

        if (i != menor) {
            troca = v[2][i]; //ordenação de graus
            v[2][i] = v[2][menor];
            v[2][menor] = troca;

            troca = v[0][i]; //ordenação de labels
            v[0][i] = v[0][menor];
            v[0][menor] = troca;
        }
    }
}

//Welsh-Powell
//Baseado em https://iq.opengenus.org/welsh-powell-algorithm/
int heuristica1(int **mat, int dim) {

    int i, j, k;
    int **mat_vertices=(int**)malloc(sizeof(int*)*3);
    for (i=0; i<3; i++)
        mat_vertices[i]=(int*)malloc(sizeof(int)*dim);
    /* Matriz 3xdim
    A primeira linha representa o label de cada vértice
    A segunda linha representa a cor de cada vértice
    A terceira linha representa o grau de cada vértice */

    for (i=0; i < dim; i++) {
        mat_vertices[0][i] = i;
        //labels dos vertices
        mat_vertices[1][i] = -1;
        //linha que representa cores, -1 é sem cor
        mat_vertices[2][i] = 0;
        //linha que representa os graus dos vertices, inicializados com 0

        for (j=0; j < dim; j++) {
            if (mat[i][j])
                mat_vertices[2][i]++;
        }
    }

    selectionSort(mat_vertices, dim);

    int cor_atual = 0, condicao;
    for (i = dim-1; i >= 0; i--) {
        //verificando se o label não possui cor
        if (mat_vertices[1][mat_vertices[0][i]] == -1) {
            mat_vertices[1][mat_vertices[0][i]] = cor_atual;
            for (j = i-1; j >=0; j--) {
                //verifica cada vértice abaixo do recém-colorido
                condicao = 1;
                for (k = j+1; k <= i && condicao; k++) {
                    //verifica se a cor de cada k acima é a cor atual tratada
                    if (mat_vertices[1][mat_vertices[0][k]] == cor_atual) {
                        //verifica se existe aresta entre j e k
                        if (mat[mat_vertices[0][k]][mat_vertices[0][j]]) {
                            condicao = 0;
                        }
                    }
                }

                if (condicao) //se condicao continua 1, j pode ser colorido
                    mat_vertices[1][mat_vertices[0][j]] = cor_atual;
            }

            cor_atual++;

        }
    }

    for (i=0; i<3; i++) {
        free(mat_vertices[i]);
    }
    free(mat_vertices);

    return cor_atual;
}

//Guloso Sequencial
//Baseado em https://www.geeksforgeeks.org/graph-coloring-set-2-greedy-algorithm/
int heuristica2(int **mat, int dim) {

    int i, j, maior;
    int *cor_vertice = (int*)malloc(sizeof(int)*dim);
    //vetor das cores de cada vertice
    bool *cor_usada = (bool*)malloc(sizeof(bool)*dim);
    //vetor que diz se determinada cor já está sendo usada

    cor_vertice[0] = 0; //inicializa o primeiro vertice com cor 0
    cor_usada[0] = false;

    for (i=1; i < dim; i++) { //inicializa todos os outros vértices como sem cor
        cor_vertice[i] = -1;
        cor_usada[i] = false;
    }

    for (i=1; i < dim; i++) {
        for (j=0; j < dim; j++) {
            if (mat[i][j] && cor_vertice[j] != -1)
                cor_usada[cor_vertice[j]] = true;
        }
    //acha os adjacentes de cada vertice que já possuem uma cor
    //ao colocar uma cor no vetor como true, indica que ela não está disponivel

        for (j=0; j < dim && cor_usada[j]; j++);
        //encontra a primeira cor disponivel
        cor_vertice[i] = j;
        //coloca essa cor no proximo vertice

        for (j=0; j < dim; j++)
            cor_usada[j] = false;
            //zera novamente o vetor de cores disponiveis

    }

    maior = cor_vertice[0];
    for (i=1; i < dim; i++)
        if (cor_vertice[i] > maior)
            maior = cor_vertice[i];

    free(cor_vertice);
    free(cor_usada);

    return maior+1;

}
