#include "matrix_operations.h"

// 1.1. Создание и освобождение памяти под матрицу
Matrix create_matrix(int rows, int cols) {
    Matrix mat;
    mat.rows = rows;
    mat.cols = cols;
    mat.data = (double **)calloc(rows, sizeof(double *));
    for (int iter = 0; iter < rows; iter++) {
        mat.data[iter] = (double *)calloc(cols, sizeof(double));
    }
    return mat;
}

void free_matrix(Matrix mat) {
    for (int iter = 0; iter < mat.rows; iter++) {
        free(mat.data[iter]);
    }
    free(mat.data);
}

// 1.2. Ввод матрицы (предусмотреть загрузку файлов из текстового файла)
Matrix load_matrix_from_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Невозможно открыть файл!");
        exit(EXIT_FAILURE);
    }

    int rows, cols;
    if (fscanf(file, "%d %d", &rows, &cols) != 2) {
        fprintf(stderr, "Ошибка чтения размеров матрицы!\n");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    Matrix mat = create_matrix(rows, cols);

    for (int iter = 0; iter < rows; iter++) {
        for (int iter_2 = 0; iter_2 < cols; iter_2++) {
            if (fscanf(file, "%lf", &mat.data[iter][iter_2]) != 1) {
                fprintf(stderr, "Ошибка чтения матричных данных!\n");
                fclose(file);
                free_matrix(mat);
                exit(EXIT_FAILURE);
            }
        }
    }

    fclose(file);
    return mat;
}

// 1.4. Копирование матриц
Matrix copy_matrix(Matrix mat) {
    Matrix copy = create_matrix(mat.rows, mat.cols);
    for (int iter = 0; iter < mat.rows; iter++) {
        for (int iter_2 = 0; iter_2 < mat.cols; iter_2++) {
            copy.data[iter][iter_2] = mat.data[iter][iter_2];
        }
    }
    return copy;
}

// 1.5. Операция сложения матриц
Matrix plus_matrices(Matrix mat1, Matrix mat2) {
    if (mat1.rows != mat2.rows || mat1.cols != mat2.cols) {
        fprintf(stderr, "Размеры матриц не совпадают для сложения!\n");
        exit(EXIT_FAILURE);
    }

    Matrix result = create_matrix(mat1.rows, mat1.cols);
    for (int iter = 0; iter < mat1.rows; iter++) {
        for (int iter_2 = 0; iter_2 < mat1.cols; iter_2++) {
            result.data[iter][iter_2] = mat1.data[iter][iter_2] + mat2.data[iter][iter_2];
        }
    }
    return result;
}

// 1.6. Операция умножения матриц
Matrix multiply_matrices(Matrix mat1, Matrix mat2) {
    if (mat1.cols != mat2.rows) {
        fprintf(stderr, "Размеры матриц не совпадают для умножения!\n");
        exit(EXIT_FAILURE);
    }

    Matrix result = create_matrix(mat1.rows, mat2.cols);
    for (int iter = 0; iter < mat1.rows; iter++) {
        for (int iter_2 = 0; iter_2 < mat2.cols; iter_2++) {
            result.data[iter][iter_2] = 0;
            for (int k = 0; k < mat1.cols; k++) {
                result.data[iter][iter_2] += mat1.data[iter][k] * mat2.data[k][iter_2];
            }
        }
    }
    return result;
}

// 1.7. Транспонирование матрицы
Matrix transpose_matrix(Matrix mat) {
    Matrix result = create_matrix(mat.cols, mat.rows);
    for (int iter = 0; iter < mat.rows; iter++) {
        for (int iter_2 = 0; iter_2 < mat.cols; iter_2++) {
            result.data[iter_2][iter] = mat.data[iter][iter_2];
        }
    }
    return result;
}

// 1.8. Нахождение детерминанта (рекурсивный метод)
double determinant(Matrix mat) {
    if (mat.rows != mat.cols) {
        fprintf(stderr, "Для вычисления определителя матрица должна быть квадратной!\n");
        exit(EXIT_FAILURE);
    }

    if (mat.rows == 1) {
        return mat.data[0][0];
    }

    if (mat.rows == 2) {
        return mat.data[0][0] * mat.data[1][1] - mat.data[0][1] * mat.data[1][0];
    }

    double det = 0;
    for (int col = 0; col < mat.cols; col++) {
        Matrix submat = create_matrix(mat.rows - 1, mat.cols - 1);
        for (int iter = 1; iter < mat.rows; iter++) {
            int subcol = 0;
            for (int iter_2 = 0; iter_2 < mat.cols; iter_2++) {
                if (iter_2 == col) continue;
                submat.data[iter - 1][subcol] = mat.data[iter][iter_2];
                subcol++;
            }
        }
        double subdet = determinant(submat);
        det += (col % 2 == 0 ? 1 : -1) * mat.data[0][col] * subdet;
        free_matrix(submat);
    }
    return det;
}

// 1.9. Операция вычитания матриц
Matrix subtract_matrices(Matrix mat1, Matrix mat2) {
    if (mat1.rows != mat2.rows || mat1.cols != mat2.cols) {
        fprintf(stderr, "Размеры матриц не совпадают для вычитания!\n");
        exit(EXIT_FAILURE);
    }

    Matrix result = create_matrix(mat1.rows, mat1.cols);
    for (int iter = 0; iter < mat1.rows; iter++) {
        for (int iter_2 = 0; iter_2 < mat1.cols; iter_2++) {
            result.data[iter][iter_2] = mat1.data[iter][iter_2] - mat2.data[iter][iter_2];
        }
    }
    return result;
}