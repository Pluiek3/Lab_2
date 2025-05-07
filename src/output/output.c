/**
 * @file output.c
 * @brief Реализация функций вывода матриц
 * @ingroup Matrix_Output-Input
 */

#include "output.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Печатает матрицу с заданной точностью
 * @param mat Указатель на матрицу для печати
 * @param precision Количество знаков после запятой
 *
 * @note Если матрица не существует (NULL), выводит сообщение об ошибке
 * @note Формат вывода: элементы разделены пробелами, строки разделены переносами
 */
void print_matrix(const Matrix *mat, int precision) {
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

/**
 * @brief Сохраняет матрицу в файл
 * @param mat Указатель на матрицу для сохранения
 * @param filename Имя файла для сохранения
 * @return 0 в случае успеха, -1 при ошибке
 *
 * @note Формат файла:
 * - Первая строка: количество строк и столбцов
 * - Последующие строки: элементы матрицы
 * - Элементы сохраняются с фиксированной точностью 6 знаков после запятой
 */
int save_matrix_to_file(const Matrix *mat, const char *filename) {
    if (mat == NULL || mat->data == NULL || filename == NULL) {
        fprintf(stderr, "Ошибка: Неверные входные параметры!\n");
        return -1;
    }

    FILE *file = fopen(filename, "w");
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

/**
 * @brief Печатает матрицу с пользовательским форматом
 * @param mat Указатель на матрицу для печати
 * @param format Строка формата printf для элементов матрицы
 *
 * @note Пример формата: "%8.2f " для выравнивания по 8 символам с 2 знаками после запятой
 * @note Проверяет валидность входных параметров
 */
void print_matrix_formatted(const Matrix *mat, const char *format) {
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