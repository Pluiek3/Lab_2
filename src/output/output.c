#include "output.h"
#include <stdio.h>
#include <stdlib.h>

void print_matrix(const Matrix* mat, int precision) {
    if (mat == NULL || mat->data == NULL) {
        fprintf(stderr, "Ошибка: Неверная матрица!\n");
        return;
    }

    char format[10];
    snprintf(format, sizeof(format), "%%.%df ", precision);

    for (int iter = 0; iter < mat->rows; iter++) {
        for (int iter_2 = 0; iter_2 < mat->cols; iter_2++) {
            printf(format, mat->data[iter][iter_2]);
        }
        printf("\n");
    }
}

int save_matrix_to_file(const Matrix* mat, const char* filename) {
    if (mat == NULL || mat->data == NULL || filename == NULL) {
        fprintf(stderr, "Ошибка: Неверные входные параметры!\n");
        return -1;
    }

    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        perror("Ошибка открытя файла!");
        return -1;
    }

    // Размеры матрицы
    fprintf(file, "%d %d\n", mat->rows, mat->cols);

    // Данные матрицы
    for (int iter = 0; iter < mat->rows; iter++) {
        for (int iter_2 = 0; iter_2 < mat->cols; iter_2++) {
            fprintf(file, "%.6f ", mat->data[iter][iter_2]);
        }
        fprintf(file, "\n");
    }

    fclose(file);
    return 0;
}

void print_matrix_formatted(const Matrix* mat, const char* format) {
    if (mat == NULL || mat->data == NULL || format == NULL) {
        fprintf(stderr, "Ошибка: Неверные входные параметры!\n");
        return;
    }

    for (int iter = 0; iter < mat->rows; iter++) {
        for (int iter_2 = 0; iter_2 < mat->cols; iter_2++) {
            printf(format, mat->data[iter][iter_2]);
        }
        printf("\n");
    }
}
