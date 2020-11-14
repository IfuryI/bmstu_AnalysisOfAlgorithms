#include <iostream>
#include "../src/matrix_multiplication.h"
#include "main_test.h"


typedef unsigned long long ull;
inline ull rdtsc()
{
    unsigned int lo, hi;
    asm volatile ( "rdtsc\n" : "=a" (lo), "=d" (hi) );
    return ((ull)hi << 32) | lo;
}

int time_test(int n1, int m1, int n2, int m2)
{
    if ((n1 < 1 || m1 < 1 || n2 < 1 || m2 < 1) || m1 != n2)
    {
        return -1;
    }

    IMatr_t matr = alloc_matrix(n1, m1);
    input_matrix2(matr, n1, m1);

    IMatr_t matr2 = alloc_matrix(n2, m2);
    input_matrix2(matr2, n2, m2);

    IMatr_t ((*arr[3]))(IMatr_t, int, int, IMatr_t, int, int);
    arr[0] = classic_mult_matrix;
    arr[1] = vinograd_mult_matrix;
    arr[2] = vinograd_optimized_mult_matrix;

    std::cout << "size: " << n1 << " " << m1 << " " << n2 << " " << m2 << " " << "[TIME] = ";

    for (int i = 0; i < 3; i++)
    {
        int count = 150;

        ull avg_time = 0;

        for (int j = 0; j < count; j++)
        {
            ull t1 = rdtsc();
            arr[i](matr, n1, m1, matr2, n2, m2);
            ull t2 = rdtsc();

            avg_time = avg_time + (t2 - t1);
        }

        std::cout << avg_time / count << " ";
    }

    free_matrix(matr, n1);
    free_matrix(matr2, n2);
    std::cout << std::endl;

    return 0;
}

int main_test()
{
    int n1, m1, n2, m2;

    std::cout << "Input size 1 [n, m]: " << std::endl;
    std::cin >> n1 >> m1;

    if (n1 < 1 || m1 < 1)
    {
        std::cout << "Size can't be less than 1" << std::endl;

        return -1;
    }

    std::cout << "Input size 2 [n, m]: " << std::endl;
    std::cin >> n2 >> m2;

    if (n2 < 1 || m2 < 1)
    {
        std::cout << "Size can't be less than 1" << std::endl;

        return -1;
    }

    if (m1 != n2)
    {
        std::cout << "Can't multiplied matrix with this size " << std::endl;

        return -1;
    }

    IMatr_t matr1 = alloc_matrix(n1, m1);
    IMatr_t matr2 = alloc_matrix(n2, m2);

    std::cout << "Input matrix: " << std::endl;
    input_matrix(matr1, n1, m1);

    std::cout << "Input matrix: " << std::endl;
    input_matrix(matr2, n2, m2);

    std::cout << "Classic: " << std::endl;
    print_matrix(classic_mult_matrix(matr1, n1, m1, matr2, n2, m2), n1, m2);
    std::cout << "Vinograd: " << std::endl;
    print_matrix(vinograd_mult_matrix(matr1, n1, m1, matr2, n2, m2), n1, m2);
    std::cout << "Optimized Vinograd: " << std::endl;
    print_matrix(vinograd_optimized_mult_matrix(matr1, n1, m1, matr2, n2, m2), n1, m2);



//    time_test(1, 1, 1, 1);
//    time_test(2, 2, 2, 2);
//    time_test(3, 3, 3, 3);
//    time_test(10, 10, 10, 10);
//    time_test(25, 25, 25, 25);
//    time_test(50, 50, 50, 50);
//
//    std::cout << "Even size:" << std::endl;
//    time_test(100, 100, 100, 100);
//    time_test(200, 200, 200, 200);
//    time_test(300, 300, 300, 300);
//    time_test(400, 400, 400, 400);
//    time_test(500, 500, 500, 500);
//
//    std::cout << "Odd size:" << std::endl;
//    time_test(101, 101, 101, 101);
//    time_test(201, 201, 201, 201);
//    time_test(301, 301, 301, 301);
//    time_test(401, 401, 401, 401);
//    time_test(501, 501, 501, 501);

    return 0;
}
