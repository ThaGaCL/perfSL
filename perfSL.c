#include "perfSL.h"

int_t encontraMax(real_t **A, int_t i, int_t n){
    real_t max = 0;
    int_t iPivo = i;

    for (int j = 0; j < n; i++) {
        if (ABS(A[i][j]) > max) {
            max = ABS(A[i][j]);
            iPivo = i;
        }
    }

}

void eliminacaoGaussPivoteamento(real_t **A, real_t *b, int_t n){
    
    for (int i=0; i < n; i++) {
        int_t iPivo = encontraMax(A, i, n);
        
        if(i != iPivo)
            // trocaLinha(A, b, i, iPivo, n);

        for (int k = i+1; k < n; k++){
            real_t m = A[k][i] / A[i][i];
            A[k][i] = 0;

            for (int j = i+1; j < n; j++){
                A[k][j] -= m * A[i][j];
            }

            b[k] -= m * b[i];
        }    
    }

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
    printf("\n----------------------------------------\n");

}