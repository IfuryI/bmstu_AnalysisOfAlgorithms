#ifndef INC_2_MATRIX_MULTIPLICATION_H
#define INC_2_MATRIX_MULTIPLICATION_H


#include "util.h"


IMatr_t classic_mult_matrix(IMatr_t matr1, int n1, int m1, IMatr_t matr2, int n2, int m2);
IMatr_t vinograd_mult_matrix(IMatr_t matr1, int n1, int m1, IMatr_t matr2, int n2, int m2);
IMatr_t vinograd_optimized_mult_matrix(IMatr_t matr1, int n1, int m1, IMatr_t matr2, int n2, int m2);


#endif //INC_2_MATRIX_MULTIPLICATION_H
