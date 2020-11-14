#include <iostream>
#include "util.h"


IMatr_t alloc_matrix(int n, int m)
{
    IMatr_t matrix = new IArr_t [n];

    for (int i = 0; i < n; i++)
    {
        matrix[i] = new int [m];
    }

    return matrix;
}

void free_matrix(IMatr_t matrix, int n)
{
    for (int i = 0; i < n; i++)
    {
        delete [] matrix[i];
    }
    delete [] matrix;
}

int input_matrix(IMatr_t matr, int n, int m)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            std::cin >> matr[i][j];
        }
    }
}

int input_matrix2(IMatr_t matr, int n, int m)
{
//    std::ifstream inf("test.txt");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
//            inf >> matr[i][j];
            matr[i][j] = i + j;
        }
    }
}

void print_matrix(IMatr_t matr, int n, int m)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            std::cout << matr[i][j] << " ";
        }
        std::cout << std::endl;
    }
}
