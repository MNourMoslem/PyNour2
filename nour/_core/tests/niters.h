#ifndef NOUR__CORE_SRC_NOUR_TESTS_NITERS_H
#define NOUR__CORE_SRC_NOUR_TESTS_NITERS_H

#include "common.h"
#include "nour/nour.h"
#include "../src/nour/niter.h"
#include "../src/nour/node_core.h"
#include "../src/nour/free.h"

#define CREATE_NODE(var, arr, ndim, shape, dtype)                     \
    do {                                                              \
        var = Node_New(arr, 1, ndim, shape, dtype);                   \
        if (!var) return -1;                                          \
    } while (0)

#define FREE_NODE_IF_ERROR(cond, node)                                \
    do {                                                              \
        if (cond) {                                                   \
            Node_Free(node);                                          \
            return -1;                                                \
        }                                                             \
    } while (0)

#define VALIDATE_ITERATOR_RESULT(cond, node)                          \
    do {                                                              \
        if (cond) {                                                   \
            Node_Free(node);                                          \
            return -1;                                                \
        }                                                             \
    } while (0)


#define VALIDATE_ITER_RESULTS(iter_ptr, type, resarr, res) do{\
    NIter_ITER(iter_ptr);\
    int __i = 0;\
    if (!NIter_NOTDONE(iter_ptr)){\
        res = -1;\
        break;\
    }\
    while (NIter_NOTDONE(iter_ptr))\
    {\
        if (*(type*)NIter_ITEM(iter_ptr) != resarr[__i++]){\
            res = -1;\
            break;\
        }\
        NIter_NEXT(iter_ptr);\
    }\
} while(0)


#define VALIDATE_MULTI_ITER_RESULTS(PMIT, type, RES)  do {       \
    type __val1, __val2;                                         \
    NMultiIter_ITER(PMIT);                                       \
    while (NMultiIter_NOTDONE(PMIT)) {                           \
        __val1 = *(type*)NMultiIter_ITEM(PMIT, 0);               \
        __val2 = *(type*)NMultiIter_ITEM(PMIT, 1);               \
                                                                 \
        if (__val1 != __val2) {                                  \
            RES = -1;                                            \
            break;                                               \
        }                                                        \
                                                                 \
        NMultiIter_NEXT(PMIT);                                   \
    }                                                            \
} while (0)

#define VALIDATE_WINDOW_ITER_RESULTS(PWIT, type, reswin, RES) do { \
    int i = 0, j = 0;\
    NWindowIter_ITER(PWIT);\
    while (NWindowIter_NOTDONE(PWIT)) {\
        type* cwin = reswin[i++];\
        if (cwin[0] != *(type*)NWindowIter_ITEM(PWIT)) {\
            res = -1;\
            break;\
        }\
        NWindowIter_ITER_WINDOW(PWIT);\
        while (NWindowIter_NOTDONE_WINDOW(PWIT)) {\
            if (cwin[j++] != *(type*)NWindowIter_ITEM_WINDOW(PWIT)) {\
                res = -1;\
                break;\
            }\
            NWindowIter_NEXT_WINDOW(PWIT);\
        }\
        if (res != 0) break;\
        j = 0;\
        NWindowIter_NEXT(PWIT);\
    }\
} while(0)

 
NR_STATIC int test_niters_1() {
    nr_int arr1[] = {1, 2, 3, 4, 5, 6};
    nr_size_t shape1[] = {2, 3};
    nr_int arr2[] = {5, 3};
    nr_size_t shape2[] = {2, 1};
    NR_DTYPE dtype = NR_INT32;

    Node* node1;
    Node* node2;

    CREATE_NODE(node1, arr1, 2, shape1, dtype);
    CREATE_NODE(node2, arr2, 2, shape2, dtype);

    NMultiIter mit;
    Node* nodes[] = {node1, node2};
    int res = NMultiIter_New(nodes, 2, &mit);

    Node_Free(node1);
    Node_Free(node2);

    return res;
}

NR_STATIC int test_niters_2() {
    nr_int arr1[] = {5, 5, 5, 3, 3, 3};
    nr_size_t shape1[] = {2, 3};
    nr_int arr2[] = {5, 3};
    nr_size_t shape2[] = {2, 1};
    NR_DTYPE dtype = NR_INT32;

    Node* node1;
    Node* node2;

    CREATE_NODE(node1, arr1, 2, shape1, dtype);
    CREATE_NODE(node2, arr2, 2, shape2, dtype);

    NMultiIter mit;
    Node* nodes[] = {node1, node2};
    int res = NMultiIter_New(nodes, 2, &mit);
    FREE_NODE_IF_ERROR(res != 0, node1);
    FREE_NODE_IF_ERROR(res != 0, node2);

    VALIDATE_MULTI_ITER_RESULTS(&mit, nr_int, res);

    Node_Free(node1);
    Node_Free(node2);

    return res;
}

NR_STATIC int test_niters_3() {
    nr_int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
    nr_size_t shape[] = {4, 4};
    nr_size_t window_dims[] = {2, 2};
    NR_DTYPE dtype = NR_INT32;

    nr_int* reswin[] = {
        (nr_int[]){1, 2, 5, 6}, (nr_int[]){2, 3, 6, 7}, (nr_int[]){3, 4, 7, 8},
        (nr_int[]){5, 6, 9, 10}, (nr_int[]){6, 7, 10, 11}, (nr_int[]){7, 8, 11, 12},
        (nr_int[]){9, 10, 13, 14}, (nr_int[]){10, 11, 14, 15}, (nr_int[]){11, 12, 15, 16}
    };

    Node* node;
    CREATE_NODE(node, arr, 2, shape, dtype);

    NWindowIter wit;
    int res = NWindowIter_New(node, &wit, window_dims, NULL, NULL);
    VALIDATE_ITERATOR_RESULT(res != 0, node);

    VALIDATE_WINDOW_ITER_RESULTS(&wit, nr_int, reswin, res);

    Node_Free(node);
    return res;
}

NR_STATIC int test_niters_4(){
    nr_int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
    nr_size_t shape[] = {4, 4};
    nr_size_t window_dims[] = {2, 2};
    nr_size_t strides_factor[] = {2, 2};
    int ndim1 = 2;

    NR_DTYPE dtype = NR_INT32;

    Node* node = Node_New(arr, 1, ndim1, shape, dtype);
    if (!node){
        return -1;
    }

    NWindowIter wit;
    NWindowIter* pwit = &wit;
    int res = NWindowIter_New(node, pwit, window_dims, strides_factor, NULL);
    if (res != 0){
        Node_Free(node);
        return -1;
    }
    pwit->iter_mode = NITER_MODE_STRIDED;

    nr_int win1[] = {1, 2, 5, 6};
    nr_int win2[] = {3, 4, 7, 8};
    nr_int win3[] = {9, 10, 13, 14};
    nr_int win4[] = {11, 12, 15, 16};

    nr_int* reswin[] =  {win1, win2, win3, win4};

    VALIDATE_WINDOW_ITER_RESULTS(pwit, nr_int, reswin, res);

    Node_Free(node);

    return res;
}

NR_STATIC int test_niters_5(){
    Node* node;
    _NEW_NODE_4x4_INT32(node);
    if (!node){
        return -1;
    }

    nr_size_t window_dims[] = {2, 2};
    nr_size_t strides_factor[] = {1, 1};
    nr_size_t dilation[] = {2, 2};

    NWindowIter wit;
    NWindowIter* pwit = &wit;
    int res = NWindowIter_New(node, pwit, window_dims, strides_factor, dilation);
    if (res != 0){
        Node_Free(node);
        return -1;
    }
    pwit->iter_mode = NITER_MODE_STRIDED;

    nr_int win1[] = {1, 3, 9, 11};
    nr_int win2[] = {2, 4, 10, 12};
    nr_int win3[] = {5, 7, 13, 15};
    nr_int win4[] = {6, 8, 14, 16};

    nr_int* reswin[] =  {win1, win2, win3, win4};

    VALIDATE_WINDOW_ITER_RESULTS(pwit, nr_int, reswin, res);

    Node_Free(node);

    return res;
}

static int test_niters_6(){
    Node* node;
    _NEW_NODE_3x3_FLOAT32(node);
    if (!node){
        return -1;
    }

    nr_float32 resarr[] = {1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f};

    NIter iter;
    NIter_FromNode(&iter, node, NITER_MODE_STRIDED);

    int res;
    VALIDATE_ITER_RESULTS(&iter, nr_float32, resarr, res);

    Node_Free(node);

    return 0;
}

void test_niters(){
    NTEST_RUN_TEST("Nour Iterators",
    {
        NTEST_ONE_TEST(1, test_niters_1);
        NTEST_ONE_TEST(2, test_niters_2);
        NTEST_ONE_TEST(3, test_niters_3);
        NTEST_ONE_TEST(4, test_niters_4);
        NTEST_ONE_TEST(5, test_niters_5);
        NTEST_ONE_TEST(6, test_niters_6);
    }
    )
}


#endif