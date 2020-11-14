#include <iostream>
#include "util.h"


vector<vector<int>>* CreateMatrForLevDist(int n, int m)
{
    auto *DistMatr = new vector<vector<int>>(n, vector<int>(m));

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            (*DistMatr)[i][j] = i + j;
        }
    }
    (*DistMatr)[0][0] = 0;

    return DistMatr;
}

vector<vector<int>>* CreateMatrForLevDist2(int n, int m)
{
    auto *DistMatr = new vector<vector<int>>(n, vector<int>(m));

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            (*DistMatr)[i][j] = -1;
        }
    }
    (*DistMatr)[0][0] = 0;

    return DistMatr;
}

int PrintLevDistMatr(vector<vector<int>>* DistMatr)
{
    for (int i = 0; i < (*DistMatr).size(); i++)
    {
        cout << '\n';
        for (int j = 0; j < (*DistMatr)[i].size(); j++)
        {
            cout << (*DistMatr)[i][j] << " ";
        }
    }

    cout << '\n';

    return 0;
}

int FreeLevDistMatr(vector<vector<int>>* DistMatr)
{
    (*DistMatr).clear();
    (*DistMatr).shrink_to_fit();

    return 0;
}