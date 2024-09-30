#include <stdio.h>
#include <stdlib.h>
#include "likwid.h"
#include "utils.h"
#include "perfSL.h"
#include "matrix.h"


int main(int argc, char *argv[])
{
    int_t n;
    real_t **A, *b;
    real_t **Ac, *bc;

    double s_time = 0.0;
    double e_time = 0.0;
    double t_time = 0.0;

    LIKWID_MARKER_INIT;

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
    LIKWID_MARKER_START("EG_TRADICIONAL");
    s_time = timestamp();
    eliminacaoGaussPivoteamento(Ac, bc, n);
    e_time = timestamp();
    LIKWID_MARKER_STOP("EG_TRADICIONAL");
    // // imprimeEntrada(Ac, bc, n);

    t_time = e_time - s_time;
    // // Vetor solucao
    real_t *x = malloc(n * sizeof(real_t));
    real_t *r = malloc(n * sizeof(real_t));
    retrosSubs(Ac, bc, x, n);
    calculaResiduo(A, x, b, r, n);
    imprimeSaida(x, n, r, t_time);

    free(x);
    free(r);

    copiaEntrada(A, b, Ac, bc, n);

    // GS - Iterativo
    real_t *x1 = malloc(n * sizeof(real_t));
    real_t *r1 = malloc(n * sizeof(real_t));
    LIKWID_MARKER_START("GS_ITERATIVO");
    s_time = timestamp();
    iterativoGaussSeidel(Ac, bc, x1, n, 0.0001, 50);
    e_time = timestamp();
    LIKWID_MARKER_STOP("GS_ITERATIVO");
    calculaResiduo(Ac, x1, bc, r1, n);
    t_time = e_time - s_time;
    imprimeSaida(x1, n, r1, t_time);

    free(x1);
    free(r1);

    // EG - TRIDIAGONAL
    // Vetores diagonais

    copiaEntrada(A, b, Ac, bc, n);

    // GS - TRIDIAGONAL
    real_t *c = malloc((n - 1) * sizeof(real_t));
    real_t *d = malloc(n * sizeof(real_t));
    real_t *a = malloc((n - 1) * sizeof(real_t));
    real_t *r2 = malloc(n * sizeof(real_t));
    real_t *x2 = malloc(n * sizeof(real_t));

    separaDiagonal(Ac, d, a, c, n);

    LIKWID_MARKER_START("EG_TRIDIAGONAL");
    s_time = timestamp();
    eliminacaoGaussTridiagonal(d, a, c, bc, x2, n);
    e_time = timestamp();
    LIKWID_MARKER_STOP("EG_TRIDIAGONAL");
    calculaResiduo(Ac, x2, bc, r2, n);
    t_time = e_time - s_time;
    imprimeSaida(x2, n, r2, t_time);

    // SG - TRIDIAGONAL
    real_t *r3 = malloc(n * sizeof(real_t));
    real_t *x3 = malloc(n * sizeof(real_t));

    copiaEntrada(A, b, Ac, bc, n);
    // imprimeEntrada(Ac, bc, n);
    separaDiagonal(Ac, d, a, c, n);

    LIKWID_MARKER_START("GS_TRIDIAGONAL");
    s_time = timestamp();
    gaussSeidelTridiagonal(a, bc, c, x3, d, n, 0.0001, 50);
    e_time = timestamp();
    LIKWID_MARKER_STOP("GS_TRIDIAGONAL");
    calculaResiduo(Ac, x3, bc, r3, n);
    t_time = e_time - s_time;
    imprimeSaida(x3, n, r3, t_time);

    free(x2);
    free(r2);
    free(r3);
    free(x3);

    // Libera memoria alocada
    liberaMemoria(A, b, n);
    liberaMemoria(Ac, bc, n);

    LIKWID_MARKER_CLOSE;

    printf("/**/");
    return 0;
}
