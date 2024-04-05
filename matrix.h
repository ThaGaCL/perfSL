#ifndef MATRIX_H
#define MATRIX_H

#include "utils.h"
#include "perfSL.h"

real_t **criaMatriz(int_t n);

real_t *criaVetor(int_t n);

void leEntrada(real_t **A, real_t *b, int_t n);

void imprimeEntrada(real_t **A, real_t *b, int_t n);

void copiaEntrada(real_t **A, real_t *b, real_t **Ac, real_t *bc, int_t n);

void liberaMemoria(real_t **A, real_t *b, int_t n);

void imprimeSaida(real_t *x, int_t n, real_t *res);

#endif