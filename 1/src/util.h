#ifndef AA_1_UTIL_H
#define AA_1_UTIL_H


#include <vector>
#include <string>
using namespace std;

vector<vector<int>>* CreateMatrForLevDist(int n, int m);
vector<vector<int>>* CreateMatrForLevDist2(int n, int m);
int PrintLevDistMatr(vector<vector<int>>* DistMatr);
int FreeLevDistMatr(vector<vector<int>>* DistMatr);


#endif //AA_1_UTIL_H
