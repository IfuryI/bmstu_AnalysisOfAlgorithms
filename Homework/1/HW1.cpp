(1)     for (int i = 0; i < n1 - 1; i++)
        {
(2)         for (int j = 0; j < m1 / 2; j++)
            {
(3)             mulH[i] = mulH[i] + matr1[i][j * 2] * matr1[i][j * 2 + 1];
            }
(4)         mulH[i + 1] = 0;
        }

(5)     for (int i = 0; i < m2 - 1; i++)
        {
(6)         for (int j = 0; j < n2 / 2; j++)
            {
(7)             mulV[i] = mulV[i] + matr2[j * 2][i] * matr2[j * 2 + 1][i];
            }   
(8)         mulV[i + 1] = 0;
        }

(9)     for (int i = 0; i < n1; i++)
        {
(10)        for (int j = 0; j < m2; j++)
            {
(11)            result[i][j] = -mulH[i] - mulV[j];
(12)            for (int k = 0; k < m1 / 2; k++)
                {
(13)                result[i][j] = result[i][j] + (matr1[i][2 * k + 1] + matr2[2 * k][j]) * (matr1[i][2 * k] + matr2[2 * k + 1][j]);
                }
            }
        }

(14)    if (m1 % 2 == 1)
        {
(15)        for (int i = 0; i < n1; i++)
            {
(16)            for (int j = 0; j < m2; j++)
                {
(17)                result[i][j] = result[i][j] + matr1[i][m1 - 1] * matr2[m1 - 1][j];
                }
            }
        }