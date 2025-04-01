#ifndef MATRIX_OPERATIONS_H
#define MATRIX_OPERATIONS_H

#include <stdio.h>
#include <stdlib.h>

#include "../include/config.h"

Matrix create_matrix(int rows, int cols);
void free_matrix(Matrix mat);
Matrix load_matrix_from_file(const char *filename);
Matrix copy_matrix(Matrix mat);
Matrix plus_matrices(Matrix mat1, Matrix mat2);
Matrix multiply_matrices(Matrix mat1, Matrix mat2);
Matrix transpose_matrix(Matrix mat);
double determinant(Matrix mat);
Matrix subtract_matrices(Matrix mat1, Matrix mat2);

#endif