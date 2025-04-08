/**
 * @file main.c
 * @brief Основная программа для выполнения матричных операций
 * @mainpage Матричные вычисления
 *
 * Программа выполняет последовательность матричных операций:
 * 1. Загружает матрицы A, B, C, D из файлов.
 * 2. Вычисляет выражение: A - (B + C × D)^T.
 * 3. Выводит результаты промежуточных вычислений.
 * 4. Выполенние тестирования основных матричных операций и ввода-вывода.
 * 5. Освобождает выделенную память.
 */

#include "matrix/matrix_operations.h"
#include "output/output.h"

/**
 * @brief Точка входа в программу
 * @return 0 при успешном выполнении, EXIT_FAILURE при ошибке
 *
 * @note Матрицы загружаются из файлов в папке data/
 * @note Формат файлов матриц:
 * - Первые два числа - размеры матрицы (строки, столбцы)
 * - Последующие числа - элементы матрицы построчно
 *
 * @warning Проверяет совместимость размеров матриц перед операциями
 */
int main() {
    // Загрузка матриц из файлов
    Matrix A = load_matrix_from_file("data/A.txt");
    Matrix B = load_matrix_from_file("data/B.txt");
    Matrix C = load_matrix_from_file("data/C.txt");
    Matrix D = load_matrix_from_file("data/D.txt");

    // Вывод загруженных матриц
    printf("Matrix A:\n");
    print_matrix(&A, 2);
    printf("\nMatrix B:\n");
    print_matrix(&B, 2);
    printf("\nMatrix C:\n");
    print_matrix(&C, 2);
    printf("\nMatrix D:\n");
    print_matrix(&D, 2);

    // 1. Вычисление произведения C × D
    Matrix CD = multiply_matrices(C, D);
    printf("\n1) C * D:\n");
    print_matrix(&CD, 2);

    // 2. Вычисление суммы B + (C × D)
    Matrix B_plus_CD = plus_matrices(B, CD);
    printf("\n2) B + (C * D):\n");
    print_matrix(&B_plus_CD, 2);

    // 3. Транспонирование результата (B + C × D)^T
    Matrix B_plus_CD_transposed = transpose_matrix(B_plus_CD);
    printf("\n3) (B + C * D)**T:\n");
    print_matrix(&B_plus_CD_transposed, 2);

    // Проверка размерностей перед вычитанием
    if (A.rows != B_plus_CD_transposed.rows || A.cols != B_plus_CD_transposed.cols) {
        fprintf(stderr, "Ошибка: размеры матрицы не совпадают для вычитания A - (B + C * D)**T\n");
        fprintf(stderr, "A: %dx%d, (B+CD)^T: %dx%d\n", A.rows, A.cols, B_plus_CD_transposed.rows,
                B_plus_CD_transposed.cols);
        exit(EXIT_FAILURE);
    }

    // 4. Вычисление финального результата A - (B + C × D)^T
    Matrix result = subtract_matrices(A, B_plus_CD_transposed);
    printf("\n4) Результат A - (B + C * D)**T:\n");
    print_matrix(&result, 2);

    if (save_matrix_to_file(&result, "data/result.txt") != 0) {
        fprintf(stderr, "Ошибка при сохранении результата в файл\n");
    }

    free_matrix(A);
    free_matrix(B);
    free_matrix(C);
    free_matrix(D);
    free_matrix(CD);
    free_matrix(B_plus_CD);
    free_matrix(B_plus_CD_transposed);
    free_matrix(result);

    return 0;
}