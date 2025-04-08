/**
 * @file tests_output.c
 * @brief Тесты для функций вывода матриц
 * @ingroup Matrix_I_O_Tests
 */

#include "tests_output.h"

/**
 * @brief Создает тестовую матрицу с предсказуемыми значениями
 * @param rows Количество строк
 * @param cols Количество столбцов
 * @return Заполненная тестовая матрица
 *
 * Значения элементов рассчитываются по формуле:
 * (номер_строки + 1)*10 + (номер_столбца + 1)*0.1
 * Это позволяет легко проверять корректность вывода
 */
Matrix create_test_matrix(int rows, int cols) {
    Matrix mat;
    mat.rows = rows;
    mat.cols = cols;
    mat.data = (double **)malloc(rows * sizeof(double *));
    for (int iter = 0; iter < rows; iter++) {
        mat.data[iter] = (double *)malloc(cols * sizeof(double));
        for (int iter_2 = 0; iter_2 < cols; iter_2++) {
            mat.data[iter][iter_2] = (iter + 1) * 10 + (iter_2 + 1) * 0.1;
        }
    }
    return mat;
}

/**
 * @brief Тест базового вывода матрицы
 *
 * Проверяет:
 * - Корректность создания тестовой матрицы
 * - Отсутствие падения при выводе
 * - Сохранение структуры матрицы
 *
 * @note Проверка вывода в stdout затруднена, поэтому тестируется только отсутствие ошибок
 */
void test_print_matrix_basic(void) {
    Matrix mat = create_test_matrix(2, 3);
    CU_ASSERT(mat.rows == 2 && mat.cols == 3);

    // Проверяем, что функция не падает (вывод в stdout сложно тестировать)
    print_matrix(&mat, 1);

    free_matrix(mat);
}

/**
 * @brief Тест граничных случаев вывода
 *
 * Проверяет обработку особых случаев:
 * - NULL матрица (должна выводить сообщение об ошибке)
 * - Пустая матрица (не должна вызывать ошибок)
 */
void test_print_matrix_edge_cases(void) {
    // Тест NULL матрицы
    print_matrix(NULL, 2); // Должно вывести сообщение об ошибке

    // Тест пустой матрицы
    Matrix empty = {0};
    print_matrix(&empty, 2); // Не должно быть вывода
}

/**
 * @brief Тест сохранения матрицы в файл (нормальный случай)
 *
 * Проверяет:
 * - Корректность сохранения размеров матрицы
 * - Точность сохранения значений
 * - Соответствие формата файла спецификации
 * - Очистку временных файлов
 */
void test_save_matrix_to_file_normal(void) {
    const char *filename = "test_output_matrix.dat";
    Matrix mat = create_test_matrix(2, 2);
    CU_ASSERT(mat.rows == 2 && mat.cols == 2);

    // Сохраняем матрицу
    CU_ASSERT(save_matrix_to_file(&mat, filename) == 0);

    // Проверяем содержимое файла
    FILE *file = fopen(filename, "r");
    CU_ASSERT_PTR_NOT_NULL(file);

    int rows, cols;
    CU_ASSERT(fscanf(file, "%d %d", &rows, &cols) == 2);
    CU_ASSERT(rows == 2 && cols == 2);

    // Проверяем значения
    double val;
    for (int iter = 0; iter < 2; iter++) {
        for (int iter_2 = 0; iter_2 < 2; iter_2++) {
            CU_ASSERT(fscanf(file, "%lf", &val) == 1);
            CU_ASSERT_DOUBLE_EQUAL(val, mat.data[iter][iter_2], 0.000001);
        }
    }

    fclose(file);
    remove(filename);
    free_matrix(mat);
}

/**
 * @brief Тест обработки ошибок при сохранении
 *
 * Проверяет:
 * - Обработку NULL параметров
 * - Попытку сохранения в несуществующую директорию
 * - Возвращаемые коды ошибок
 */
void test_save_matrix_to_file_errors(void) {
    // Тест с NULL параметрами
    CU_ASSERT(save_matrix_to_file(NULL, "test.dat") == -1);
    CU_ASSERT(save_matrix_to_file(NULL, NULL) == -1);

    // Тест с несуществующей директорией
    Matrix mat = create_test_matrix(1, 1);
    CU_ASSERT(mat.rows == 1 && mat.cols == 1);
    CU_ASSERT(save_matrix_to_file(&mat, "/nonexistent_dir/test.dat") == -1);
    free_matrix(mat);
}

/**
 * @brief Тест форматированного вывода матрицы
 *
 * Проверяет:
 * - Поддержку различных форматов вывода
 * - Обработку специальных форматов (экспоненциальная запись)
 * - Отсутствие падения при выводе
 */
void test_print_matrix_formatted(void) {
    Matrix mat = create_test_matrix(1, 3);
    CU_ASSERT(mat.rows == 1 && mat.cols == 3);

    // Проверяем, что функция не падает
    print_matrix_formatted(&mat, "%8.3f ");
    print_matrix_formatted(&mat, "%+.2e ");

    free_matrix(mat);
}

/**
 * @brief Регистрирует все тесты функций вывода
 *
 * Создает тестовый набор и добавляет тесты для:
 * - Базового вывода матрицы
 * - Граничных случаев
 * - Сохранения в файл
 * - Обработки ошибок
 * - Форматированного вывода
 */
void register_output_operations_tests() {
    CU_pSuite suite = CU_add_suite("Вывод матриц", NULL, NULL);
    if (!suite) {
        CU_cleanup_registry();
        return;
    }

    CU_add_test(suite, "Базовый вывод", test_print_matrix_basic);
    CU_add_test(suite, "Граничные случаи", test_print_matrix_edge_cases);
    CU_add_test(suite, "Сохранение в файл", test_save_matrix_to_file_normal);
    CU_add_test(suite, "Ошибки сохранения", test_save_matrix_to_file_errors);
    CU_add_test(suite, "Форматированный вывод", test_print_matrix_formatted);
}