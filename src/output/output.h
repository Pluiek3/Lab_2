#ifndef MATRIX_OUTPUT_H
#define MATRIX_OUTPUT_H

#include <stdio.h>
#include <stdlib.h>

#include "../include/config.h"


void print_matrix(const Matrix* mat, int precision);

int save_matrix_to_file(const Matrix* mat, const char* filename);

void print_matrix_formatted(const Matrix* mat, const char* format);

#endif