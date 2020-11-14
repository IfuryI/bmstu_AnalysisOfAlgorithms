#ifndef INC_2_UTIL_H
#define INC_2_UTIL_H


typedef int ** IMatr_t;
typedef int * IArr_t;


IMatr_t alloc_matrix(int n, int m);
void free_matrix(IMatr_t matrix, int n);
int input_matrix(IMatr_t matr, int n, int m);
int input_matrix2(IMatr_t matr, int n, int m);
void print_matrix(IMatr_t matr, int n, int m);


#endif //INC_2_UTIL_H
