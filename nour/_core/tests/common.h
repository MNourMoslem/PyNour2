#ifndef NOUR__CORE_SRC_NOUR_TESTS_COMMON_H
#define NOUR__CORE_SRC_NOUR_TESTS_COMMON_H

#include <stdio.h>

typedef int (*TestFunc) ();

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

#define _NEW_NODE_4x4_INT32(node_ptr)                    \
    do {                                                 \
        nr_int32 __arr[] = {1, 2, 3, 4,                  \
                            5, 6, 7, 8,                  \
                            9, 10, 11, 12,               \
                            13, 14, 15, 16};             \
        nr_size_t __shape[] = {4, 4};                    \
        int __ndim = 2;                                  \
        NR_DTYPE __dtype = NR_INT32;                     \
        node_ptr = Node_New(__arr, 1,                    \
                            __ndim,                      \
                            __shape,                     \
                            __dtype);                    \
    } while (0)

#define _NEW_NODE_4x4_FLOAT64(node_ptr)                  \
    do {                                                 \
        nr_float64 __arr[] = {1, 2, 3, 4,                \
                                5, 6, 7, 8,              \
                                9, 10, 11, 12,           \
                                13, 14, 15, 16};         \
        nr_size_t __shape[] = {4, 4};                    \
        int __ndim = 2;                                  \
        NR_DTYPE __dtype = NR_FLOAT64;                   \
        node_ptr = Node_New(__arr, 1,                    \
                            __ndim,                      \
                            __shape,                     \
                            __dtype);                    \
    } while (0)

#define _NEW_NODE_2x2_INT32(node_ptr)                    \
    do {                                                 \
        nr_int32 __arr[] = {1, 2,                        \
                            3, 4};                       \
        nr_size_t __shape[] = {2, 2};                    \
        int __ndim = 2;                                  \
        NR_DTYPE __dtype = NR_INT32;                     \
        node_ptr = Node_New(__arr, 1,                    \
                            __ndim,                      \
                            __shape,                     \
                            __dtype);                    \
    } while (0)

#define _NEW_NODE_3x3_BOOL(node_ptr)                     \
    do {                                                 \
        nr_bool __arr[] = {1, 0, 1,                      \
                           0, 1, 0,                      \
                           1, 1, 0};                     \
        nr_size_t __shape[] = {3, 3};                    \
        int __ndim = 2;                                  \
        NR_DTYPE __dtype = NR_BOOL;                      \
        node_ptr = Node_New(__arr, 1,                    \
                            __ndim,                      \
                            __shape,                     \
                            __dtype);                    \
    } while (0)

#define _NEW_NODE_3x3_FLOAT32(node_ptr)                  \
    do {                                                 \
        nr_float32 __arr[] = {1.0f, 2.0f, 3.0f,          \
                              4.0f, 5.0f, 6.0f,          \
                              7.0f, 8.0f, 9.0f};         \
        nr_size_t __shape[] = {3, 3};                    \
        int __ndim = 2;                                  \
        NR_DTYPE __dtype = NR_FLOAT32;                   \
        node_ptr = Node_New(__arr, 1,                    \
                            __ndim,                      \
                            __shape,                     \
                            __dtype);                    \
    } while (0)

#define _NEW_NODE_2x2_FLOAT64(node_ptr)                  \
    do {                                                 \
        nr_float64 __arr[] = {1.0, 2.0,                  \
                              3.0, 4.0};                 \
        nr_size_t __shape[] = {2, 2};                    \
        int __ndim = 2;                                  \
        NR_DTYPE __dtype = NR_FLOAT64;                   \
        node_ptr = Node_New(__arr, 1,                    \
                            __ndim,                      \
                            __shape,                     \
                            __dtype);                    \
    } while (0)

#define _NEW_NODE_CUSTOM(node_ptr, type, arr, shape, ndim, nr_dtype) \
    do {                                                             \
        type __arr[] = arr;                                          \
        nr_size_t __shape[] = shape;                                 \
        int __ndim = ndim;                                           \
        NR_DTYPE __dtype = nr_dtype;                                 \
        node_ptr = Node_New(__arr, 1, __ndim, __shape, __dtype);     \
    } while (0)

#endif