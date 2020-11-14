#include "sort_algorithms.h"

#include <iostream>


typedef int * IArr_t;


void Bubble_Sort(IArr_t arr, int n)
{
    int i = 0;
    bool flag = true;

    while (flag)
    {
        flag = false;
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                std::swap(arr[j], arr[j + 1]);
                flag = true;
            }
        }

        i++;
    }
}

void Selection_Sort(IArr_t arr, int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        int min = i;
        for (int j = i + 1; j < n; j++)
        {
            if (arr[j] < arr[min])
            {
                min = j;
            }
        }

        std::swap(arr[i], arr[min]);
    }
}

void InsertionSort(IArr_t arr, int n)
{
    int key, j;
    for (int i = 1; i < n; i++)
    {
        key = arr[i];
        j = i - 1;

        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j--;
        }

        arr[j + 1] = key;
    }
}

