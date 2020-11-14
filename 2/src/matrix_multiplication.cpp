#include <cstdlib>
#include "matrix_multiplication.h"


IMatr_t classic_mult_matrix(IMatr_t matr1, int n1, int m1, IMatr_t matr2, int n2, int m2)
{
    IMatr_t res = alloc_matrix(n1, m2);

    for (int i = 0; i < n1; i++)
    {
        for (int j = 0; j < m2; j++)
        {
            res[i][j] = 0;
            for (int k = 0; k < m1; k++)
            {
                res[i][j] += matr1[i][k] * matr2[k][j];
            }
        }
    }

    return res;
}

IMatr_t vinograd_mult_matrix(IMatr_t matr1, int n1, int m1, IMatr_t matr2, int n2, int m2)
{
    IMatr_t result = alloc_matrix(n1, m2);

    IArr_t mulH = (IArr_t)calloc(n1, sizeof(int));

    for (int i = 0; i < n1; i++)
    {
        mulH[i] = 0;
        for (int j = 0; j < m1 / 2; j++)
        {
            mulH[i] = mulH[i] + matr1[i][j * 2] * matr1[i][j * 2 + 1];
        }
    }

    IArr_t mulV = (IArr_t)calloc(m2, sizeof(int));

    for (int i = 0; i < m2; i++)
    {
        mulV[i] = 0;
        for (int j = 0; j < n2 / 2; j++)
        {
            mulV[i] = mulV[i] + matr2[j * 2][i] * matr2[j * 2 + 1][i];
        }
    }
    for (int i = 0; i < n1; i++)
    {
        for (int j = 0; j < m2; j++)
        {
            result[i][j] = -mulH[i] - mulV[j];
            for (int k = 0; k < m1 / 2; k++)
            {
                result[i][j] = result[i][j] + (matr1[i][2 * k + 1] + matr2[2 * k][j]) * (matr1[i][2 * k] + matr2[2 * k + 1][j]);
            }
        }
    }

    if (m1 % 2 == 1)
    {
        for (int i = 0; i < n1; i++)
        {
            for (int j = 0; j < m2; j++)
            {
                result[i][j] = result[i][j] + matr1[i][m1 - 1] * matr2[m1 - 1][j];
            }
        }
    }

    return result;
}

IMatr_t vinograd_optimized_mult_matrix(IMatr_t matr1, int n1, int m1, IMatr_t matr2, int n2, int m2)
{

    if ((n1 < 1 || m1 < 1 || n2 < 1 || m2 < 1) || m1 != n2)
    {
        return nullptr;
    }

    IMatr_t result = alloc_matrix(n1, m2);

    IArr_t mulH = (IArr_t)calloc(n1, sizeof(int));

    int m1Mod2 = m1 % 2;

    for (int i = 0; i < n1; i++)
    {
        for (int j = 0; j < (m1 - m1Mod2); j += 2)
        {
            mulH[i] += matr1[i][j] * matr1[i][j + 1];
        }
    }

    IArr_t mulV = (IArr_t)calloc(m2, sizeof(int));

    int n2Mod2 = n2 % 2;

    for (int i = 0; i < m2; i++)
    {
        for (int j = 0; j < (n2 - n2Mod2); j += 2)
        {
            mulV[i] += matr2[j][i] * matr2[j + 1][i];
        }
    }

    for (int i = 0; i < n1; i++)
    {
        for (int j = 0; j < m2; j++)
        {
            int buff = -(mulH[i] + mulV[j]);
            for (int k = 0; k < (m1 - m1Mod2); k += 2)
            {
                buff += (matr1[i][k + 1] + matr2[k][j]) * (matr1[i][k] + matr2[k + 1][j]);
            }
            result[i][j] = buff;
        }
    }

    if (m1Mod2 == 1)
    {
        int m1Min_1 = m1 - 1;
        for (int i = 0; i < n1; i++)
        {
            for (int j = 0; j < m2; j++)
            {
                result[i][j] += matr1[i][m1Min_1] * matr2[m1Min_1][j];
            }
        }
    }

    return result;
}
