#ifndef MATRIX_STRUCT_H
#define MATRIX_STRUCT_H

typedef struct {
    int rows;      // Количество строк
    int cols;      // Количество столбцов
    double** data; // Указатель на данные матрицы
} Matrix;

#endif
