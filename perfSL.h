#ifndef PERFSL_H
#define PERFSL_H

#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int_t encontraMax(real_t **A, int_t i, int_t n);

void eliminacaoGaussPivoteamento(real_t **A, real_t *b, int_t n);

void retrosSubs(real_t **A, real_t *b, real_t *x, int_t n);

void iterativoGaussSeidel(real_t **A, real_t *b, real_t *x, int_t n, real_t tol, int_t maxIter);

void eliminacaoGaussTridiagonal(real_t *d, real_t *a, real_t *c, real_t *b, real_t *x, int_t n);

void gaussSeidelTridiagonal(real_t *a, real_t *b, real_t *c, real_t *x, real_t *d, int_t n, real_t tol, int_t maxIter);

real_t *separaDiagonal(real_t **A, real_t *d, real_t *a, real_t *c, int_t n);

real_t calculaResiduo(real_t **A, real_t *x, real_t *b, real_t *residuo, int_t n);

#endif