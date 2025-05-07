/**
 * @file tests_matrix.c
 * @brief Тесты для операций с матрицами
 * @ingroup Matrix_Tests
 */

#include "tests_matrix.h"

/**
 * @brief Тест создания и освобождения матрицы
 *
 * Проверяет корректность создания матрицы:
 * - Правильность установки размеров
 * - Выделение памяти
 * - Возможность записи и чтения значений
 * - Корректность освобождения памяти
 */
void test_create_and_free_matrix(void) {
    Matrix mat = create_matrix(3, 3);

    CU_ASSERT_EQUAL(mat.rows, 3);
    CU_ASSERT_EQUAL(mat.cols, 3);
    CU_ASSERT_PTR_NOT_NULL(mat.data);

    // Проверка выделенной памяти
    if (mat.data != NULL) {
        for (int iter = 0; iter < mat.rows; iter++) {
            for (int iter_2 = 0; iter_2 < mat.cols; iter_2++) {
                mat.data[iter][iter_2] = iter + iter_2;
                CU_ASSERT_EQUAL(mat.data[iter][iter_2], iter + iter_2);
            }
        }
    }

    free_matrix(mat);
}

/**
 * @brief Тест загрузки матрицы из файла
 *
 * Проверяет:
 * - Создание тестового файла с матрицей
 * - Корректность загрузки размеров
 * - Точность загрузки значений
 * - Очистку временных файлов
 */
void test_load_matrix_from_file(void) {
    // Создаем тестовый файл
    const char *filename = "test_matrix.dat";
    FILE *file = fopen(filename, "w");
    CU_ASSERT_PTR_NOT_NULL(file);

    if (file) {
        fprintf(file, "2 3\n1.5 2.5 3.5\n4.5 5.5 6.5");
        fclose(file);

        // Загружаем и проверяем
        Matrix mat = load_matrix_from_file(filename);
        CU_ASSERT_EQUAL(mat.rows, 2);
        CU_ASSERT_EQUAL(mat.cols, 3);
        CU_ASSERT_DOUBLE_EQUAL(mat.data[0][0], 1.5, 0.0001);
        CU_ASSERT_DOUBLE_EQUAL(mat.data[1][2], 6.5, 0.0001);

        // Удаляем тестовый файл
        remove(filename);
        free_matrix(mat);
    }
}

/**
 * @brief Тест копирования матрицы
 *
 * Проверяет:
 * - Создание точной копии матрицы
 * - Сохранение всех значений
 * - Независимость копии от оригинала (глубокое копирование)
 */
void test_copy_matrix(void) {
    Matrix original = create_matrix(2, 2);
    original.data[0][0] = 1.0;
    original.data[0][1] = 2.0;
    original.data[1][0] = 3.0;
    original.data[1][1] = 4.0;

    Matrix copy = copy_matrix(original);
    CU_ASSERT_EQUAL(copy.rows, 2);
    CU_ASSERT_EQUAL(copy.cols, 2);
    CU_ASSERT_DOUBLE_EQUAL(copy.data[0][0], 1.0, 0.0001);
    CU_ASSERT_DOUBLE_EQUAL(copy.data[1][1], 4.0, 0.0001);

    // Проверка глубокого копирования
    original.data[0][0] = 5.0;
    CU_ASSERT_DOUBLE_EQUAL(copy.data[0][0], 1.0, 0.0001);

    free_matrix(original);
    free_matrix(copy);
}

/**
 * @brief Тест сложения матриц
 *
 * Проверяет:
 * - Корректность поэлементного сложения
 * - Обработку матриц одинакового размера
 * - Точность вычислений с плавающей точкой
 */
void test_add_matrices(void) {
    Matrix a = create_matrix(2, 2);
    Matrix b = create_matrix(2, 2);

    a.data[0][0] = 1.0;
    a.data[0][1] = 2.0;
    a.data[1][0] = 3.0;
    a.data[1][1] = 4.0;

    b.data[0][0] = 0.5;
    b.data[0][1] = 1.5;
    b.data[1][0] = 2.5;
    b.data[1][1] = 3.5;

    Matrix result = plus_matrices(a, b);
    CU_ASSERT_DOUBLE_EQUAL(result.data[0][0], 1.5, 0.0001);
    CU_ASSERT_DOUBLE_EQUAL(result.data[1][1], 7.5, 0.0001);

    free_matrix(a);
    free_matrix(b);
    free_matrix(result);
}

/**
 * @brief Тест умножения матриц
 *
 * Проверяет:
 * - Корректность умножения матриц совместимых размеров
 * - Правильность вычисления элементов результирующей матрицы
 * - Точность вычислений с плавающей точкой
 */
void test_multiply_matrices(void) {
    Matrix a = create_matrix(2, 3);
    Matrix b = create_matrix(3, 2);

    // Заполняем тестовые матрицы
    double aval = 1.0;
    for (int iter = 0; iter < 2; iter++) {
        for (int iter_2 = 0; iter_2 < 3; iter_2++) {
            a.data[iter][iter_2] = aval++;
        }
    }

    double bval = 0.5;
    for (int iter = 0; iter < 3; iter++) {
        for (int iter_2 = 0; iter_2 < 2; iter_2++) {
            b.data[iter][iter_2] = bval++;
        }
    }

    Matrix result = multiply_matrices(a, b);
    CU_ASSERT_EQUAL(result.rows, 2);
    CU_ASSERT_EQUAL(result.cols, 2);
    CU_ASSERT_DOUBLE_EQUAL(result.data[0][0], 5.5, 0.0001);
    CU_ASSERT_DOUBLE_EQUAL(result.data[1][1], 35.0, 0.0001);

    free_matrix(a);
    free_matrix(b);
    free_matrix(result);
}

/**
 * @brief Тест транспонирования матрицы
 *
 * Проверяет:
 * - Правильность изменения размеров
 * - Корректность перестановки элементов
 * - Сохранение значений при транспонировании
 */
void test_transpose_matrix(void) {
    Matrix original = create_matrix(2, 3);
    original.data[0][0] = 1.0;
    original.data[0][1] = 2.0;
    original.data[0][2] = 3.0;
    original.data[1][0] = 4.0;
    original.data[1][1] = 5.0;
    original.data[1][2] = 6.0;

    Matrix transposed = transpose_matrix(original);
    CU_ASSERT_EQUAL(transposed.rows, 3);
    CU_ASSERT_EQUAL(transposed.cols, 2);
    CU_ASSERT_DOUBLE_EQUAL(transposed.data[0][0], 1.0, 0.0001);
    CU_ASSERT_DOUBLE_EQUAL(transposed.data[2][1], 6.0, 0.0001);

    free_matrix(original);
    free_matrix(transposed);
}

/**
 * @brief Тест вычисления определителя
 *
 * Проверяет:
 * - Расчет определителя для матрицы 2x2
 * - Расчет определителя для матрицы 3x3
 * - Точность вычислений с плавающей точкой
 */
void test_determinant(void) {
    Matrix mat2x2 = create_matrix(2, 2);
    mat2x2.data[0][0] = 1.0;
    mat2x2.data[0][1] = 2.0;
    mat2x2.data[1][0] = 3.0;
    mat2x2.data[1][1] = 4.0;

    Matrix mat3x3 = create_matrix(3, 3);
    mat3x3.data[0][0] = 2.0;
    mat3x3.data[0][1] = -1.0;
    mat3x3.data[0][2] = 3.0;
    mat3x3.data[1][0] = 0.0;
    mat3x3.data[1][1] = 4.0;
    mat3x3.data[1][2] = -2.0;
    mat3x3.data[2][0] = 1.0;
    mat3x3.data[2][1] = 0.0;
    mat3x3.data[2][2] = 5.0;

    CU_ASSERT_DOUBLE_EQUAL(determinant(mat2x2), -2.0, 0.0001);
    CU_ASSERT_DOUBLE_EQUAL(determinant(mat3x3), 42.0, 0.0001);

    free_matrix(mat2x2);
    free_matrix(mat3x3);
}

/**
 * @brief Тест вычитания матриц
 *
 * Проверяет:
 * - Корректность поэлементного вычитания
 * - Обработку матриц одинакового размера
 * - Точность вычислений с плавающей точкой
 */
void test_subtract_matrices(void) {
    Matrix a = create_matrix(2, 2);
    Matrix b = create_matrix(2, 2);

    a.data[0][0] = 5.0;
    a.data[0][1] = 5.0;
    a.data[1][0] = 5.0;
    a.data[1][1] = 5.0;

    b.data[0][0] = 1.0;
    b.data[0][1] = 2.0;
    b.data[1][0] = 3.0;
    b.data[1][1] = 4.0;

    Matrix result = subtract_matrices(a, b);
    CU_ASSERT_DOUBLE_EQUAL(result.data[0][0], 4.0, 0.0001);
    CU_ASSERT_DOUBLE_EQUAL(result.data[1][1], 1.0, 0.0001);

    free_matrix(a);
    free_matrix(b);
    free_matrix(result);
}

/**
 * @brief Регистрирует все тесты матричных операций
 *
 * Создает тестовый набор и добавляет все тестовые случаи
 * для проверки матричных операций.
 */
void register_matrix_operations_tests() {
    CU_pSuite suite = CU_add_suite("Matrix Operations", NULL, NULL);
    if (!suite) {
        CU_cleanup_registry();
        return;
    }

    CU_add_test(suite, "Создание и очистка матрицы", test_create_and_free_matrix);
    CU_add_test(suite, "Загрузка матрицы из файла", test_load_matrix_from_file);
    CU_add_test(suite, "Копирование матрицы", test_copy_matrix);
    CU_add_test(suite, "Сложение матриц", test_add_matrices);
    CU_add_test(suite, "Умножение матриц", test_multiply_matrices);
    CU_add_test(suite, "Транспонирование матрицы", test_transpose_matrix);
    CU_add_test(suite, "Детерминант матрицы", test_determinant);
    CU_add_test(suite, "Вычитание матриц", test_subtract_matrices);
}