#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

// Объявления функций регистрации тестов из других модулей
void register_matrix_operations_tests(void);
void register_output_operations_tests(void);

int main() {
    // Инициализация реестра тестов
    if (CU_initialize_registry() != CUE_SUCCESS) {
        return CU_get_error();
    }

    // Регистрация тестовых наборов
    register_matrix_operations_tests();
    register_output_operations_tests();

    // Запуск тестов
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    
    // Очистка
    CU_cleanup_registry();
    return CU_get_error();
}