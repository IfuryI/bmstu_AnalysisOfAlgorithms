#include <iostream>
#include <random>
#include "sort_algorithms.h"


int *get_sorted_arr(int n)
{
    int *arr = new int[n];

    for (int i = 0; i < n; i++)
    {
        arr[i] = i;
    }

    return arr;
}

int *get_reverse_sorted_arr(int n)
{
    int *arr = new int[n];

    for (int i = 0; i < n; i++)
    {
        arr[n - i - 1] = i;
    }

    return arr;
}

int *get_random_arr(int n)
{
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(-100000000, 100000000);

    int *arr = new int[n];

    for (int i = 0; i < n; i++)
    {
        arr[i] = dist(mt);
    }

    return arr;
}

typedef unsigned long long ull;
inline ull rdtsc()
{
    unsigned int lo, hi;
    asm volatile ( "rdtsc\n" : "=a" (lo), "=d" (hi) );
    return ((ull)hi << 32) | lo;
}


void test1()
{
    int arr_len[9] = {10, 50, 100, 250, 500, 1000, 2500, 5000, 10000};

    std::cout << "n       bubble      insertion       selection" << std::endl;

    for (int i = 0; i < 9; i++)
    {
        ull avg_time = 0;
        int count = 30;
        for (int j = 0; j < count; j++)
        {
            int *arr = get_sorted_arr(arr_len[i]);
            ull t1 = rdtsc();
            Bubble_Sort(arr, arr_len[i]);
            ull t2 = rdtsc();
            delete [] arr;

            avg_time = avg_time + (t2 - t1);
        }

        std::cout << arr_len[i] << " " << avg_time / count << " ";

        avg_time = 0;
        for (int j = 0; j < count; j++)
        {
            int *arr = get_sorted_arr(arr_len[i]);
            ull t1 = rdtsc();
            InsertionSort(arr, arr_len[i]);
            ull t2 = rdtsc();
            delete [] arr;

            avg_time = avg_time + (t2 - t1);
        }

        std::cout << avg_time / count << " ";

        avg_time = 0;
        for (int j = 0; j < count; j++)
        {
            int *arr = get_sorted_arr(arr_len[i]);
            ull t1 = rdtsc();
            Selection_Sort(arr, arr_len[i]);
            ull t2 = rdtsc();
            delete [] arr;

            avg_time = avg_time + (t2 - t1);
        }

        std::cout << avg_time / count << std::endl;
    }
}


void test2()
{
    int arr_len[9] = {10, 50, 100, 250, 500, 1000, 2500, 5000, 10000};

    std::cout << "n       bubble      insertion       selection" << std::endl;

    for (int i = 0; i < 9; i++)
    {
        ull avg_time = 0;
        int count = 30;
        for (int j = 0; j < count; j++)
        {
            int *arr = get_reverse_sorted_arr(arr_len[i]);
            ull t1 = rdtsc();
            Bubble_Sort(arr, arr_len[i]);
            ull t2 = rdtsc();
            delete [] arr;

            avg_time = avg_time + (t2 - t1);
        }

        std::cout << arr_len[i] << " " << avg_time / count << " ";

        avg_time = 0;
        for (int j = 0; j < count; j++)
        {
            int *arr = get_reverse_sorted_arr(arr_len[i]);
            ull t1 = rdtsc();
            InsertionSort(arr, arr_len[i]);
            ull t2 = rdtsc();
            delete [] arr;

            avg_time = avg_time + (t2 - t1);
        }

        std::cout << avg_time / count << " ";

        avg_time = 0;
        for (int j = 0; j < count; j++)
        {
            int *arr = get_reverse_sorted_arr(arr_len[i]);
            ull t1 = rdtsc();
            Selection_Sort(arr, arr_len[i]);
            ull t2 = rdtsc();
            delete [] arr;

            avg_time = avg_time + (t2 - t1);
        }

        std::cout << avg_time / count << std::endl;
    }
}

void test3()
{
    int arr_len[9] = {10, 50, 100, 250, 500, 1000, 2500, 5000, 10000};

    std::cout << "n       bubble      insertion       selection" << std::endl;

    for (int i = 0; i < 9; i++)
    {
        ull avg_time = 0;
        int count = 30;
        for (int j = 0; j < count; j++)
        {
            int *arr = get_random_arr(arr_len[i]);
            ull t1 = rdtsc();
            Bubble_Sort(arr, arr_len[i]);
            ull t2 = rdtsc();
            delete [] arr;

            avg_time = avg_time + (t2 - t1);
        }

        std::cout << arr_len[i] << " " << avg_time / count << " ";

        avg_time = 0;
        for (int j = 0; j < count; j++)
        {
            int *arr = get_random_arr(arr_len[i]);
            ull t1 = rdtsc();
            InsertionSort(arr, arr_len[i]);
            ull t2 = rdtsc();
            delete [] arr;

            avg_time = avg_time + (t2 - t1);
        }

        std::cout << avg_time / count << " ";

        avg_time = 0;
        for (int j = 0; j < count; j++)
        {
            int *arr = get_random_arr(arr_len[i]);
            ull t1 = rdtsc();
            Selection_Sort(arr, arr_len[i]);
            ull t2 = rdtsc();
            delete [] arr;

            avg_time = avg_time + (t2 - t1);
        }

        std::cout << avg_time / count << std::endl;
    }
}

int *copy(const int *arr, int n)
{
    int *new_arr = new int[n];

    for (int i = 0; i < n; i++)
    {
        new_arr[i] = arr[i];
    }

    return new_arr;
}

void print_arr(const int *arr, int n)
{
    for (int i = 0; i < n; i++)
    {
        std::cout << arr[i] << " ";
    }

    std::cout << std::endl;
}

int main_test()
{
    std::cout << "Array size: " << std::endl;

    int n;
    std::cin >> n;

    if (n < 1)
    {
        std::cout << "Wrong size" << std::endl;
        return -1;
    }

    int *arr = new int[n];

    for (int i = 0; i < n; i++)
    {
        std::cin >> arr[i];
    }

    int *buf = copy(arr, n);
    std::cout << "Your array: " << std::endl;
    print_arr(buf, n);

    std::cout << "Bubble sort" << std::endl;
    Bubble_Sort(buf, n);
    print_arr(buf, n);

    std::cout << "Insertion sort" << std::endl;
    buf = copy(arr, n);
    InsertionSort(buf, n);
    print_arr(buf, n);

    std::cout << "Selection sort" << std::endl;
    buf = copy(arr, n);
    Selection_Sort(buf, n);
    print_arr(buf, n);

    delete [] arr;
    delete [] buf;

    return 0;
}