#include "perfSL.h"
#include "utils.h"
#include "matrix.h"

#define TOLE 0.0001
#define MAXITER 50

int_t encontraMax(real_t **A, int_t i, int_t n)
{
    real_t max = 0;
    int_t iPivo = i;

    for (int j = 0; j < n; j++)
    {
        if (ABS(A[i][j]) > max)
        {
            max = ABS(A[i][j]);
            iPivo = i;
        }
    }

    return iPivo;
}

// Troca a linha i pela linha iPivo
void trocaLinha(real_t **A, real_t *b, int_t i, int_t iPivo, int_t n)
{
    real_t aux = 0;
    for (int j = 0; j < n; j++)
    {
        aux = A[i][j];
        A[i][j] = A[iPivo][j];
        A[iPivo][j] = aux;
    }
    aux = b[i];
    b[i] = b[iPivo];
    b[iPivo] = aux; // Adicionado para completar a troca
}

void eliminacaoGaussPivoteamento(real_t **A, real_t *b, int_t n)
{

    printf("EG clássico:\n");

    for (int i = 0; i < n; i++)
    {
        int_t iPivo = encontraMax(A, i, n);
        if (i != iPivo)
            trocaLinha(A, b, i, iPivo, n);

        for (int k = i + 1; k < n; k++)
        {
            real_t m = A[k][i] / A[i][i];
            A[k][i] = 0;

            for (int j = i + 1; j < n; j++)
            {
                A[k][j] -= m * A[i][j];
            }

            b[k] -= m * b[i];
        }
    }
}

void retrosSubs(real_t **A, real_t *b, real_t *x, int_t n)
{
    // printf("RS:\n");
    for (int i = n - 1; i >= 0; i--)
    {
        x[i] = b[i];
        for (int j = i + 1; j < n; j++)
        {
            x[i] -= A[i][j] * x[j];
        }
        x[i] /= A[i][i];
    }
}

void iterativoGaussSeidel(real_t **A, real_t *b, real_t *x, int_t n, real_t tol, int_t maxIter)
{
    printf("GS classico [ %ld iterações ]:\n", maxIter);
    real_t *x0 = malloc(n * sizeof(real_t));
    real_t erro = tol + 1;
    int_t iter = 0;

    while (erro > tol && iter < maxIter)
    {
        for (int i = 0; i < n; i++)
        {
            x0[i] = x[i];
            x[i] = b[i];
            for (int j = 0; j < n; j++)
            {
                if (j != i)
                {
                    x[i] -= A[i][j] * x[j];
                }
            }
            x[i] /= A[i][i];
        }

        erro = 0;
        for (int i = 0; i < n; i++)
        {
            erro += ABS(x[i] - x0[i]);
        }

        iter++;
    }

    free(x0);
}

real_t *separaDiagonal(real_t **A, real_t *d, real_t *a, real_t *c, int_t n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i == j)
            {
                d[i] = A[i][j];
            }
            else if (i == j - 1)
            {
                c[i] = A[i][j];
            }
            else if (i == j + 1)
            {
                a[i - 1] = A[i][j];
            }
        }
    }
}

void eliminacaoGaussTridiagonal(real_t *d, real_t *a, real_t *c, real_t *x, int_t n)
{
    printf("EG tridiagonal:\n");
    // para cada linha
    for (int i = 0; i < n; i++)
    {
        real_t m = a[i] / d[i];
        a[i] = 0.0;
        d[i + 1] -= m * c[i];
        x[i + 1] -= m * x[i];
    }
}

real_t calculaResiduo(real_t **A, real_t *x, real_t *b, real_t *residuo, int_t n)
{
    int_t i, j;
    real_t soma;

    for (i = 0; i < n; i++)
    {
        soma = 0.0;
        for (j = 0; j < n; j++)
        {
            soma += A[i][j] * x[j];
        }
        residuo[i] = b[i] - soma;
    }
}