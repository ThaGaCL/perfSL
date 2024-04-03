#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "perfSL.h"

int main(int argc, char *argv[]){
    int_t n = malloc((int_t)sizeof(int_t));
    real_t **A, *b;

    printf("Digite a ordem da matriz: ");
    scanf("%ld", &n);

    A = malloc(n * sizeof(real_t *));
    for (int i = 0; i < n; i++) {
        A[i] = malloc(n * sizeof(real_t));
    }

    b = malloc(n * sizeof(real_t));

    leEntrada(A, b, n);
    imprimeEntrada(A, b, n);

    eliminacaoGaussPivoteamento(A, b, n);
    imprimeEntrada(A, b, n);

    return 0;

}

