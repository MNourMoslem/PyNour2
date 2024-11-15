#ifndef NOUR__CORE_SRC_NOUR_TESTS_COMMON_H
#define NOUR__CORE_SRC_NOUR_TESTS_COMMON_H

#include <stdio.h>

#define NTEST_HEAD(test_name)\
printf("===========================\n");\
printf(test_name);\
printf("\n");\
printf("===========================\n");

#define NTEST_TAIL \
printf("===========================\n");


#define NTEST_ONE_TEST(id, func)\
printf("Test %i: %s\n", id, func() == 0 ? "Success" : "Failuer");

#define NTEST_RUN_TEST(test_name, test_units)\
NTEST_HEAD(test_name) \
test_units \
NTEST_TAIL

#endif