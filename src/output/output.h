/**
 * @file output.h
 * @brief Заголовочный файл для функций вывода матриц
 * @ingroup Matrix_Output-Input
 * @{
 */

#ifndef MATRIX_OUTPUT_H
#define MATRIX_OUTPUT_H

#include <stdio.h>
#include <stdlib.h>
#include "../include/config.h"

/**
 * @brief Выводит матрицу в стандартный вывод с заданной точностью
 * @param mat Указатель на матрицу для вывода
 * @param precision Количество знаков после десятичной точки
 *
 * @note Если mat == NULL, выводит сообщение об ошибке в stderr
 * @note Формат вывода: элементы разделены пробелами, строки разделены переносами
 */
void print_matrix(const Matrix *mat, int precision);

/**
 * @brief Сохраняет матрицу в файл
 * @param mat Указатель на матрицу для сохранения
 * @param filename Имя файла для сохранения
 * @return 0 при успешном сохранении, -1 при ошибке
 *
 * @note Формат файла:
 * - Первая строка: количество строк и столбцов
 * - Последующие строки: элементы матрицы
 * @warning При ошибке открытия файла возвращает -1 и выводит сообщение в stderr
 */
int save_matrix_to_file(const Matrix *mat, const char *filename);

/**
 * @brief Выводит матрицу с пользовательским форматированием
 * @param mat Указатель на матрицу для вывода
 * @param format Строка формата printf для элементов
 *
 * @note Примеры форматов:
 * - "%8.3f " - выравнивание по 8 символам, 3 знака после точки
 * - "%+.2e " - экспоненциальная запись со знаком
 * @warning Не проверяет валидность строки формата
 */
void print_matrix_formatted(const Matrix *mat, const char *format);

#endif

/** @} */