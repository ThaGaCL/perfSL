#include "matrix.h"

real_t **criaMatriz(int_t n){
    real_t **A = malloc(n * sizeof(real_t *));
    for (int i = 0; i < n; i++) {
        A[i] = malloc(n * sizeof(real_t));
    }
    return A;
}

real_t *criaVetor(int_t n){
    real_t *b = malloc(n * sizeof(real_t));
    return b;
}

void leEntrada(real_t **A, real_t *b, int_t n){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            scanf("%lf", &A[i][j]);
        }
        scanf("%lf", &b[i]);
    }
} 

void imprimeEntrada(real_t **A, real_t *b, int_t n){
    printf("Matriz A:\n");
    printf("----------------------------------------\n");
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            printf("%lf | ", A[i][j]);
        }
        printf("\n");
    }
    printf("----------------------------------------\n");

    printf("\nVetor b:\n");
    printf("----------------------------------------\n");    
    for(int i = 0; i < n; i++){
        printf("%lf |", b[i]);
    }
    printf("\n----------------------------------------\n\n");

}

void copiaEntrada(real_t **A, real_t *b, real_t **Ac, real_t *bc, int_t n){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            Ac[i][j] = A[i][j];
        }
        bc[i] = b[i];
    }
}

void imprimeSaida(real_t *x, int_t n, real_t *res, double t_time){
    // printf("Vetor x:\n");
    printf("%lf ms\n", t_time);
    for(int i = 0; i < n; i++){
        printf("%lf ", x[i]);
    }
    printf("\n");
    // printf("\n\nResíduo: \n\n");
    for(int i = 0; i < n; i++){
        printf("%lf ", res[i]);
    }
    printf("\n");
}

void liberaMemoria(real_t **A, real_t *b, int_t n){
    for (int i = 0; i < n; i++) {
        free(A[i]);
    }
    free(A);
    free(b);
}