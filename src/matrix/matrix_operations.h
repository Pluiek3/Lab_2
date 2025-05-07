/**
 * @file matrix_operations.h
 * @brief Заголовочный файл с объявлениями операций над матрицами
 * @defgroup Matrix_Operations
 * @{
 */

#ifndef MATRIX_OPERATIONS_H
#define MATRIX_OPERATIONS_H

#include <stdio.h>
#include <stdlib.h>
#include "../include/config.h"

/**
 * @brief Создает матрицу заданного размера
 * @param rows Количество строк
 * @param cols Количество столбцов
 * @return Новая матрица с выделенной памятью
 * @note Все элементы инициализируются нулями
 */
Matrix create_matrix(int rows, int cols);

/**
 * @brief Освобождает память, занятую матрицей
 * @param mat Матрица для освобождения
 */
void free_matrix(Matrix mat);

/**
 * @brief Загружает матрицу из файла
 * @param filename Путь к файлу с матрицей
 * @return Загруженная матрица
 * @note Формат файла: первые два числа - размеры, затем элементы построчно
 * @warning В случае ошибки чтения завершает программу с EXIT_FAILURE
 */
Matrix load_matrix_from_file(const char *filename);

/**
 * @brief Создает глубокую копию матрицы
 * @param mat Исходная матрица
 * @return Независимая копия матрицы
 */
Matrix copy_matrix(Matrix mat);

/**
 * @brief Складывает две матрицы
 * @param mat1 Первая матрица
 * @param mat2 Вторая матрица
 * @return Результат сложения
 * @note Матрицы должны быть одинакового размера
 * @warning При несовпадении размеров завершает программу с EXIT_FAILURE
 */
Matrix plus_matrices(Matrix mat1, Matrix mat2);

/**
 * @brief Умножает две матрицы
 * @param mat1 Первая матрица (m×n)
 * @param mat2 Вторая матрица (n×k)
 * @return Результат умножения (m×k)
 * @note Число столбцов mat1 должно совпадать с числом строк mat2
 * @warning При несовместимых размерах завершает программу с EXIT_FAILURE
 */
Matrix multiply_matrices(Matrix mat1, Matrix mat2);

/**
 * @brief Транспонирует матрицу
 * @param mat Исходная матрица (m×n)
 * @return Транспонированная матрица (n×m)
 */
Matrix transpose_matrix(Matrix mat);

/**
 * @brief Вычисляет определитель матрицы
 * @param mat Квадратная матрица
 * @return Значение определителя
 * @note Используется рекурсивный метод разложения
 * @warning Для неквадратных матриц завершает программу с EXIT_FAILURE
 */
double determinant(Matrix mat);

/**
 * @brief Вычитает две матрицы
 * @param mat1 Первая матрица
 * @param mat2 Вторая матрица
 * @return Результат вычитания
 * @note Матрицы должны быть одинакового размера
 * @warning При несовпадении размеров завершает программу с EXIT_FAILURE
 */
Matrix subtract_matrices(Matrix mat1, Matrix mat2);

#endif

/** @} */