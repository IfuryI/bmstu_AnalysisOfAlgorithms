#include <iostream>
#include <ctime>
#include <unistd.h>
#include "src/util.h"


int LevDist(string str1, string str2)
{
    vector<vector<int>> *DistMatr = CreateMatrForLevDist(str1.size() + 1, str2.size() + 1);

    for (int i = 1; i < (*DistMatr).size(); i++)
    {
        for (int j = 1; j < (*DistMatr)[i].size(); j++)
        {
            (*DistMatr)[i][j] = min((*DistMatr)[i - 1][j] + 1,
                                min((*DistMatr)[i][j - 1] + 1,
                                    (*DistMatr)[i - 1][j - 1]+ (str1[i - 1] == str2[j - 1] ? 0 : 1)));
        }
    }

    int dist = (*DistMatr)[str1.size()][str2.size()];

    FreeLevDistMatr(DistMatr);

    return dist;
}

int RLevDist(string str1, string str2)
{
    if (str1 == "" or str2 == "")
    {
        return abs((int)(str1.size() - str2.size()));
    }

    return min(RLevDist(str1.substr(0, str1.size() - 1), str2) + 1,
           min(RLevDist(str1, str2.substr(0, str2.size() - 1)) + 1,
               RLevDist(str1.substr(0, str1.size() - 1), str2.substr(0, str2.size() - 1))
               + (str1[str1.size() - 1] == str2[str2.size() - 1] ? 0 : 1)));
}

//int RMatrLevDist_RECURSION(string str1, string str2, vector<vector<int>> *DistMatr)
//{
//    if (str1 == "" or str2 == "")
//    {
//        return abs((int)(str1.size() - str2.size()));
//    }
//
//    int value = min(RMatrLevDist_RECURSION(str1.substr(0, str1.size() - 1), str2, DistMatr) + 1,
//                min(RMatrLevDist_RECURSION(str1, str2.substr(0, str2.size() - 1), DistMatr) + 1,
//                    RMatrLevDist_RECURSION(str1.substr(0, str1.size() - 1),
//                                           str2.substr(0, str2.size() - 1), DistMatr)
//                                           + (str1[str1.size() - 1] == str2[str2.size() - 1] ? 0 : 1)));
//
//    (*DistMatr)[str1.size()][str2.size()] = value;
//
//    return value;
//}

int RMatrLevDist_RECURSION2(string str1, string str2, vector<vector<int>> *DistMatr)
{
    if (str1.size() == 0)
    {
        (*DistMatr)[str1.size()][str2.size()] = str2.size();
    }
    else if (str2.size() == 0)
    {
        (*DistMatr)[str1.size()][str2.size()] = str1.size();
    }
    else
    {
        if ((*DistMatr)[str1.size()][str2.size() - 1] == -1)
        {
            (*DistMatr)[str1.size()][str2.size() - 1] = RMatrLevDist_RECURSION2(str1, str2.substr(0, str2.size() - 1), DistMatr);
        }

        if ((*DistMatr)[str1.size() - 1][str2.size()] == -1)
        {
            (*DistMatr)[str1.size() - 1][str2.size()] = RMatrLevDist_RECURSION2(str1.substr(0, str1.size() - 1), str2, DistMatr);
        }

        if ((*DistMatr)[str1.size() - 1][str2.size() - 1] == -1)
        {
            (*DistMatr)[str1.size() - 1][str2.size() - 1] = RMatrLevDist_RECURSION2(str1.substr(0, str1.size() - 1), str2.substr(0, str2.size() - 1), DistMatr);
        }

        int value = (str1[str1.size() - 1] == str2[str2.size() - 1] ? 0 : 1);
        (*DistMatr)[str1.size()][str2.size()] = min((*DistMatr)[str1.size() - 1][str2.size()] + 1,
                                                min((*DistMatr)[str1.size()][str2.size() - 1] + 1,
                                                    (*DistMatr)[str1.size() - 1][str2.size() - 1] + value));

    }
    return (*DistMatr)[str1.size()][str2.size()];
}

int RMatrLevDist(string str1, string str2)
{
    vector<vector<int>> *DistMatr = CreateMatrForLevDist2(str1.size() + 1, str2.size() + 1);

    int dist = RMatrLevDist_RECURSION2(str1, str2, DistMatr);

    FreeLevDistMatr(DistMatr);

    return dist;
}

int Dam_LevDist(string str1, string str2)
{
    vector<vector<int>> *DistMatr = CreateMatrForLevDist(str1.size() + 1, str2.size() + 1);

    for (int i = 1; i < (*DistMatr).size(); i++)
    {
        for (int j = 1; j < (*DistMatr)[i].size(); j++)
        {
            (*DistMatr)[i][j] = min((*DistMatr)[i - 1][j] + 1,
                                min((*DistMatr)[i][j - 1] + 1,
                                    (*DistMatr)[i - 1][j - 1] + (str1[i - 1] == str2[j - 1] ? 0 : 1)));

            if ((i > 1 and j > 1) and str1[i - 1] == str2[j - 2] and str1[i - 2] == str2[j - 1])
            {
                (*DistMatr)[i][j] = min((*DistMatr)[i][j], (*DistMatr)[i - 2][j - 2] + 1);
            }
        }
    }

    int dist = (*DistMatr)[str1.size()][str2.size()];

    FreeLevDistMatr(DistMatr);

    return dist;
}

typedef unsigned long long ull;
inline ull rdtsc() {
    unsigned int lo, hi;
    asm volatile ( "rdtsc\n" : "=a" (lo), "=d" (hi) );
    return ((ull)hi << 32) | lo;
}

string gen_random(const int len) {

    string tmp_s;
    static const char alphanum[] =
            "0123456789"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz";

    srand( (unsigned) time(NULL) * getpid());

    for (int i = 0; i < len; ++i)
        tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];


    return tmp_s;

}

int test(int len1, int len2)
{
    cout << "test woth [len1, len2] = " << len1 << ", " << len2 << endl;

    int ((*arr[4]))(std::string, std::string);
    arr[0] = LevDist;
    arr[1] = RLevDist;
    arr[2] = RMatrLevDist;
    arr[3] = Dam_LevDist;

    string str1 = gen_random(len1);
    string str2 = gen_random(len2);

    for (int i = 0; i < 4; i++)
    {
        ull avg_time = 0;
        int count = 300;
        for (int j = 0; j < count; j++)
        {
            ull t1 = rdtsc();

            arr[i](str1, str2);

            ull t2 = rdtsc();
            avg_time += t2 - t1;
        }

        cout << "alg" << i << ": " << avg_time / count << " ";
    }
    cout << endl;

    return 0;
}


int main()
{
    int ((*arr[4]))(std::string, std::string);
    arr[0] = LevDist;
    arr[1] = RLevDist;
    arr[2] = RMatrLevDist;
    arr[3] = Dam_LevDist;

    string str1;
    string str2;

    cout << "str1 =";
    cin >> str1;
    cout << "str2 =";
    cin >> str2;

//    cout << RMatrLevDist(str1, str2);
    cout << "ML RL RML DLM" << endl;
    if (str1 != "" && str2 != "") {
        for (int i = 0; i < 4; i++) {
            cout << arr[i](str1, str2) << " ";
        }
    }
    cout << endl;
//
//    test(1, 1);
//    test(2, 2);
//    test(3, 3);
//    test(4, 4);
//    test(5, 5);
//    test(6, 6);
//    test(7, 7);




    return 0;
}
