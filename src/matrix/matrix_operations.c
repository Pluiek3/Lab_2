/**
 * @file matrix_operations.c
 * @brief Файл для операций с матрицами
 * @defgroup Matrix_Operations
 * @{
 */

#include "matrix_operations.h"

/**
 * @brief Создает матрицу заданного размера
 * @param rows Количество строк
 * @param cols Количество столбцов
 * @return Созданная матрица
 */
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

/**
 * @brief Освобождает память, занятую матрицей
 * @param mat Матрица для освобождения
 */
void free_matrix(Matrix mat) {
    for (int iter = 0; iter < mat.rows; iter++) {
        free(mat.data[iter]);
    }
    free(mat.data);
}

/**
 * @brief Загружает матрицу из файла
 * @param filename Имя файла для загрузки
 * @return Загруженная матрица
 * @note Формат файла: первые два числа - размеры матрицы, затем элементы построчно
 */
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

/**
 * @brief Создает копию матрицы
 * @param mat Исходная матрица
 * @return Копия матрицы
 */
Matrix copy_matrix(Matrix mat) {
    Matrix copy = create_matrix(mat.rows, mat.cols);
    for (int iter = 0; iter < mat.rows; iter++) {
        for (int iter_2 = 0; iter_2 < mat.cols; iter_2++) {
            copy.data[iter][iter_2] = mat.data[iter][iter_2];
        }
    }
    return copy;
}

/**
 * @brief Складывает две матрицы
 * @param mat1 Первая матрица
 * @param mat2 Вторая матрица
 * @return Результат сложения
 * @note Матрицы должны быть одинакового размера
 */
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

/**
 * @brief Умножает две матрицы
 * @param mat1 Первая матрица
 * @param mat2 Вторая матрица
 * @return Результат умножения
 * @note Количество столбцов первой матрицы должно совпадать с количеством строк второй
 */
Matrix multiply_matrices(Matrix mat1, Matrix mat2) {
    if (mat1.cols != mat2.rows) {
        fprintf(stderr, "Размеры матриц не совпадают для умножения!\n");
        exit(EXIT_FAILURE);
    }

    Matrix result = create_matrix(mat1.rows, mat2.cols);
    for (int iter = 0; iter < mat1.rows; iter++) {
        for (int iter_2 = 0; iter_2 < mat2.cols; iter_2++) {
            result.data[iter][iter_2] = 0;
            for (int iter_3 = 0; iter_3 < mat1.cols; iter_3++) {
                result.data[iter][iter_2] += mat1.data[iter][iter_3] * mat2.data[iter_3][iter_2];
            }
        }
    }
    return result;
}

/**
 * @brief Транспонирует матрицу
 * @param mat Исходная матрица
 * @return Транспонированная матрица
 */
Matrix transpose_matrix(Matrix mat) {
    Matrix result = create_matrix(mat.cols, mat.rows);
    for (int iter = 0; iter < mat.rows; iter++) {
        for (int iter_2 = 0; iter_2 < mat.cols; iter_2++) {
            result.data[iter_2][iter] = mat.data[iter][iter_2];
        }
    }
    return result;
}

/**
 * @brief Вычисляет определитель матрицы
 * @param mat Квадратная матрица
 * @return Значение определителя
 * @note Используется рекурсивный метод разложения по первой строке
 */
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
                if (iter_2 == col)
                    continue;
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

/**
 * @brief Вычитает две матрицы
 * @param mat1 Первая матрица
 * @param mat2 Вторая матрица
 * @return Результат вычитания
 * @note Матрицы должны быть одинакового размера
 */
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