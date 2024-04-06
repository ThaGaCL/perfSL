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

void eliminacaoGaussTridiagonal(real_t *d, real_t *a, real_t *c, real_t *b, real_t *x, int_t n)
{
    printf("EG tridiagonal:\n");

    // TRIANGULARIZAÇÃO: 5(n-1) operações
    for (int i = 0; i < n - 1; ++i)
    {
        double m = a[i] / d[i];
        a[i] = 0.0;
        d[i + 1] -= c[i] * m;
        b[i + 1] -= b[i] * m;
    }
    // RETROSUBSTITUIÇÃO: ≈ 3n operações (n grande)
    x[n - 1] = b[n - 1] / d[n - 1];
    for (int i = n - 2; i >= 0; --i)
        x[i] = (b[i] - c[i] * x[i + 1]) / d[i];
}

real_t maxNorm(real_t *x, real_t *old_x, int_t n)
{
    real_t max = 0;
    for (int i = 0; i < n; i++)
    {
        real_t diff = ABS(x[i] - old_x[i]);
        if (diff > max)
        {
            max = diff;
        }
    }
    return max;
}

void gaussSeidelTridiagonal(real_t *a, real_t *b, real_t *c, real_t *x, real_t *d, int_t n, real_t tol, int_t maxIter)
{
    printf("GS tridiagonal [ %ld iterações ]:\n", maxIter);
    real_t erro = 1.0 + tol;
    real_t *old_x = malloc(n * sizeof(real_t));

    while (erro > tol && maxIter > 0)
    {
        for (int_t i = 0; i < n; i++)
        {
            old_x[i] = x[i];
        }
        x[0] = (b[0] - c[0] * x[1]) / d[0];
        for (int i = 1; i < n - 1; ++i)
        {
            x[i] = (b[i] - a[i - 1] * x[i - 1] - c[i] * x[i + 1]) / d[i];
        }

        x[n - 1] = (b[n - 1] - a[n - 2] * x[n - 2]) / d[n - 1];
        maxIter--;

        // Calcula erro == norma máxima de ( x^(k) – x^(k-1) )
        erro = maxNorm(x, old_x, n);
        printf("Erro: %f\n", erro);
    }
}

void calculaResiduo(real_t **A, real_t *x, real_t *b, real_t *residuo, int_t n)
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