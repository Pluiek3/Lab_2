/**
 * @file tests_matrix.h
 * @brief Заголовочный файл для тестов операций с матрицами
 * @ingroup Matrix_Tests
 */

 #ifndef TESTS_MATRIX_H
 #define TESTS_MATRIX_H
 
 #include <stdio.h>
 #include <stdlib.h>
 #include <CUnit/CUnit.h>
 #include <CUnit/Basic.h>
 #include "../src/matrix/matrix_operations.h"
 
 /**
  * @brief Регистрирует все тестовые случаи для операций с матрицами
  * 
  * Данная функция создает тестовый набор для операций с матрицами и добавляет
  * в него все индивидуальные тестовые случаи. Тесты включают:
  * - Создание матриц и управление памятью
  * - Операции ввода/вывода с файлами
  * - Базовые арифметические операции
  * - Свойства матриц и преобразования
  * - Особые случаи и граничные условия
  * 
  * @note Эту функцию необходимо вызывать перед запуском любых тестов матриц
  * @see matrix_operations.h
  */
 void register_matrix_operations_tests(void);
 
 #endif /* TESTS_MATRIX_H */