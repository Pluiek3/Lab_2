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

void register_output_operations_tests(void);

#endif