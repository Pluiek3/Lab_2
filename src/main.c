#include "matrix/matrix_operations.h" 
#include "output/output.h"

int main() {
    Matrix A = load_matrix_from_file("data/A.txt");
    Matrix B = load_matrix_from_file("data/B.txt");
    Matrix C = load_matrix_from_file("data/C.txt");
    Matrix D = load_matrix_from_file("data/D.txt");

    printf("Matrix A:\n");
    print_matrix(&A, 2);
    printf("\nMatrix B:\n");
    print_matrix(&B, 2);
    printf("\nMatrix C:\n");
    print_matrix(&C, 2);
    printf("\nMatrix D:\n");
    print_matrix(&D, 2);

    // Вычисление C × D
    Matrix CD = multiply_matrices(C, D);
    printf("\n1) C * D:\n");
    print_matrix(&CD, 2);

    // Вычисление B + (C × D)
    Matrix B_plus_CD = plus_matrices(B, CD);
    printf("\n2) B + (C * D):\n");
    print_matrix(&B_plus_CD, 2);

    // Транспонирование (B + C × D)
    Matrix B_plus_CD_transposed = transpose_matrix(B_plus_CD);
    printf("\n3) (B + C * D)**T:\n");
    print_matrix(&B_plus_CD_transposed, 2);

    // Проверка размерностей перед вычитанием
    if (A.rows != B_plus_CD_transposed.rows || A.cols != B_plus_CD_transposed.cols) {
        fprintf(stderr, "Размеры матрицы не совпадают для вычитания A - (B + C * D)**T\n");
        exit(EXIT_FAILURE);
    }

    // Вычисление A - (B + C × D)^T
    Matrix result = subtract_matrices(A, B_plus_CD_transposed);
    printf("\n4) Результат A - (B + C * D)**T:\n");
    print_matrix(&result, 2);

    // Освобождение памяти
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