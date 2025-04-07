#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

void register_matrix_operations_tests(void);
void register_output_operations_tests(void);

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