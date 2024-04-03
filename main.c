#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "perfSL.h"
#include "matrix.h"

int main(int argc, char *argv[]){
    int_t n = malloc((int_t)sizeof(int_t));
    real_t **A, *b;
    real_t **Ac, *bc;

    printf("Digite a ordem da matriz: ");
    scanf("%ld", &n);

    A = criaMatriz(n);
    b = criaVetor(n);

    Ac = criaMatriz(n);
    bc = criaVetor(n);


    leEntrada(A, b, n);
    imprimeEntrada(A, b, n);

    copiaEntrada(A, b, Ac, bc, n);

    eliminacaoGaussPivoteamento(Ac, bc, n);
    imprimeEntrada(Ac, bc, n);

    // Vetor solucao
    real_t *x = malloc(n * sizeof(real_t));
    retrosSubs(Ac, bc, x, n);
    imprimeEntrada(Ac, x, n);

    copiaEntrada(A, b, Ac, bc, n);
    copiaEntrada(A, b, Ac, bc, n);

    // IGS
    real_t *x1 = malloc(n * sizeof(real_t));
    iterativoGaussSeidel(A, b, x1, n, 0.0001, 50);
    imprimeEntrada(A, x1, n);

    return 0;

}

