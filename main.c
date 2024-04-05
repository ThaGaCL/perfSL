#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "perfSL.h"
#include "matrix.h"

int main(int argc, char *argv[]){
    int_t n;
    real_t **A, *b;
    real_t **Ac, *bc;

    // printf("Digite a ordem da matriz: ");
    scanf("%ld", &n);

    A = criaMatriz(n);
    b = criaVetor(n);

    Ac = criaMatriz(n);
    bc = criaVetor(n);


    leEntrada(A, b, n);
    // imprimeEntrada(A, b, n);

    copiaEntrada(A, b, Ac, bc, n);

    // EG - Pivoteamento
    eliminacaoGaussPivoteamento(Ac, bc, n);
    // imprimeEntrada(Ac, bc, n);

    // Vetor solucao
    real_t *x = malloc(n * sizeof(real_t));
    real_t *r = malloc(n * sizeof(real_t));
    retrosSubs(Ac, bc, x, n);
    calculaResiduo(A, x, b, r, n);
    imprimeSaida(x, n, r);

    copiaEntrada(A, b, Ac, bc, n);
    copiaEntrada(A, b, Ac, bc, n);

    // GS - Iterativo
    real_t *x1 = malloc(n * sizeof(real_t));
    iterativoGaussSeidel(A, b, x1, n, 0.0001, 50);
    calculaResiduo(A, x1, b, r, n);
    imprimeSaida(x1, n, r);
    // imprimeEntrada(A, x1, n);


    // EG - TRIDIAGONAL
    // eliminacaoGaussTridiagonal(A, b, n);
    // imprimeEntrada(A, b, n);

    // Libera memoria alocada
    liberaMemoria(A, b, n);
    liberaMemoria(Ac, bc, n);
    free(x);
    free(x1);

    return 0;

}

