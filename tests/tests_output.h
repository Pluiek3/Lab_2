/**
 * @file tests_output.h
 * @brief Заголовочный файл для тестирования функций вывода матриц
 * @ingroup Matrix_I_O_Tests
 * 
 * Содержит объявления функций для тестирования:
 * - Базового вывода матриц
 * - Форматированного вывода
 * - Сохранения матриц в файлы
 * - Обработки граничных случаев
 */

 #ifndef TESTS_OUTPUT_H
 #define TESTS_OUTPUT_H
 
 #include <stdio.h>
 #include <string.h>
 #include <stdlib.h>
 #include <sys/stat.h>
 #include <math.h>
 #include <CUnit/CUnit.h>
 #include <CUnit/Basic.h>
 #include "../src/include/config.h"
 #include "../src/matrix/matrix_operations.h"
 #include "../src/output/output.h"
 
 /**
  * @brief Регистрирует все тесты для функций вывода матриц
  * 
  * Создает тестовый набор и добавляет следующие тестовые случаи:
  * - test_print_matrix_basic: Тестирование базового вывода матрицы
  * - test_print_matrix_edge_cases: Тестирование граничных случаев
  * - test_save_matrix_to_file_normal: Тестирование сохранения в файл
  * - test_save_matrix_to_file_errors: Тестирование обработки ошибок
  * - test_print_matrix_formatted: Тестирование форматированного вывода
  * 
  * @note Должен вызываться перед запуском тестов CU_BasicRun()
  * @see output.h
  */
 void register_output_operations_tests(void);
 
 #endif /* TESTS_OUTPUT_H */