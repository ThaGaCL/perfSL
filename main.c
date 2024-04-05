#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "perfSL.h"
#include "matrix.h"

int main(int argc, char *argv[])
{
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

    // imprimeEntrada(A, b, n);s

    copiaEntrada(A, b, Ac, bc, n);

    // EG - Pivoteamento
    eliminacaoGaussPivoteamento(Ac, bc, n);
    // // imprimeEntrada(Ac, bc, n);

    // // Vetor solucao
    real_t *x = malloc(n * sizeof(real_t));
    real_t *r = malloc(n * sizeof(real_t));
    retrosSubs(Ac, bc, x, n);
    calculaResiduo(A, x, b, r, n);
    imprimeSaida(x, n, r);

    copiaEntrada(A, b, Ac, bc, n);
    copiaEntrada(A, b, Ac, bc, n);

    // GS - Iterativo
    real_t *x1 = malloc(n * sizeof(real_t));
    real_t *r1 = malloc(n * sizeof(real_t));
    iterativoGaussSeidel(Ac, bc, x1, n, 0.0001, 50);
    calculaResiduo(Ac, x1, bc, r1, n);
    imprimeSaida(x1, n, r1);

    // EG - TRIDIAGONAL
    // Vetores diagonais
    
    copiaEntrada(A, b, Ac, bc, n);
    
    real_t *c = malloc((n - 1) * sizeof(real_t));
    real_t *d = malloc(n * sizeof(real_t));
    real_t *a = malloc((n - 1) * sizeof(real_t));
    real_t *r2 = malloc(n * sizeof(real_t));
    real_t *x2 = malloc(n * sizeof(real_t));

    separaDiagonal(Ac, d, a, c, n);

    eliminacaoGaussTridiagonal(d, a, c, bc, x2, n);
    calculaResiduo(Ac, x2, bc, r2, n);
    imprimeSaida(x2, n, r2);

    // GS - TRIDIAGONAL
    real_t *r3 = malloc(n * sizeof(real_t));
    real_t *x3 = malloc(n * sizeof(real_t));
    
    copiaEntrada(A, b, Ac, bc, n);

    gaussSeidelTridiagonal(a, d, c, x3, bc, n, 0.0001, 50);
    calculaResiduo(Ac, x3, bc, r3, n);
    imprimeSaida(x3, n, r3);

    // Libera memoria alocada
    liberaMemoria(A, b, n);
    liberaMemoria(Ac, bc, n);
    free(x);
    free(x1);
    free(x2);
    free(x3);
    free(r);
    free(r1);
    free(r2);
    free(r3);
    free(a);
    free(c);
    free(d);
    
    
    return 0;
}
