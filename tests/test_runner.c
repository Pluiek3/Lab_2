/**
 * @file test_runner.c
 * @brief Запуск тестов
 * @ingroup Run_Matrix_Tests
 */

#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

/**
 * @brief Регистрирует тесты, связанные с операциями над матрицами.
 *
 * Эта функция должна содержать вызовы CU_add_test() для добавления
 * отдельных тестов для операций над матрицами.
 */
void register_matrix_operations_tests(void);

/**
 * @brief Регистрирует тесты, связанные с операциями вывода.
 *
 * Эта функция должна содержать вызовы CU_add_test() для добавления
 * отдельных тестов для операций вывода.
 */
void register_output_operations_tests(void);

/**
 * @brief Главная функция, которая инициализирует фреймворк тестирования CUnit,
 * регистрирует тестовые наборы и запускает тесты.
 *
 * Эта функция инициализирует реестр тестов CUnit, регистрирует
 * тесты операций с матрицами и вывода, устанавливает основной режим
 * работы в подробный, выполняет тесты и очищает реестр.
 *
 * @return Возвращает 0 при успехе или ненулевой код ошибки, если
 * инициализация или выполнение тестов не удались.
 */
int main() {
    if (CU_initialize_registry() != CUE_SUCCESS) {
        return CU_get_error();
    }

    register_matrix_operations_tests();
    register_output_operations_tests();

    CU_basic_set_mode(CU_BRM_VERBOSE);
    
    CU_basic_run_tests();

    CU_cleanup_registry();
    return CU_get_error();
}
