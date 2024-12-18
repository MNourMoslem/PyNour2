#ifndef NOUR__CORE_SRC_NOUR_TESTS_TEST_NMATH_H
#define NOUR__CORE_SRC_NOUR_TESTS_TEST_NMATH_H

#include <math.h>

#include "nour/nour.h"
#include "common.h"
#include "../src/nour/niter.h"
#include "../src/nour/node_core.h"
#include "../src/nour/free.h"
#include "../src/nour/nmath.h"

static int test_nmath_1(){
    Node *n1, *n2, *n3;
    _NEW_NODE_4x4_INT32(n1);
    if (!n1){
        return -1;
    }

    _NEW_NODE_4x4_INT32(n2);
    if (!n2){
        Node_Free(n1);
        return -1;
    }

    n3 = NMath_Add(NULL, n1, n2);
    if (!n3){
        return -1;
    }

    int res = 0;
    int nitems = Node_NItems(n3);
    nr_int32 val1, val2, val3;
    for (int i = 0; i < nitems; i++){
        val3 = *((nr_int32*)n3->data + i);
        val2 = *((nr_int32*)n2->data + i);
        val1 = *((nr_int32*)n1->data + i);

        if (val3 != val1 + val2){
            res = -1;
            break;
        }
    }

    Node_Free(n1);
    Node_Free(n2);
    Node_Free(n3);

    return res;
}

static int test_nmath_2(){
    Node *n1, *n2, *n3;
    _NEW_NODE_4x4_INT32(n1);
    if (!n1){
        return -1;
    }

    _NEW_NODE_4x4_INT32(n2);
    if (!n2){
        Node_Free(n1);
        return -1;
    }

    NR_RMVFLG(n2->flags, NR_NODE_CONTIGUOUS);

    n3 = NMath_Mul(NULL, n1, n2);
    if (!n3){
        return -1;
    }

    int res = 0;
    int nitems = Node_NItems(n3);
    nr_int32 val1, val2, val3;
    for (int i = 0; i < nitems; i++){
        val3 = *((nr_int32*)n3->data + i);
        val2 = *((nr_int32*)n2->data + i);
        val1 = *((nr_int32*)n1->data + i);

        if (val3 != val1 * val2){
            res = -1;
            break;
        }
    }

    Node_Free(n1);
    Node_Free(n2);
    Node_Free(n3);

    return res;
}

static int test_nmath_3(){
    Node *n1, *n2, *n3;
    _NEW_NODE_4x4_INT32(n1);
    if (!n1){
        return -1;
    }

    _NEW_NODE_4x4_INT32(n2);
    if (!n2){
        Node_Free(n1);
        return -1;
    }

    NR_RMVFLG(n1->flags, NR_NODE_CONTIGUOUS);
    NR_RMVFLG(n2->flags, NR_NODE_CONTIGUOUS);

    n3 = NMath_Mul(NULL, n1, n2);
    if (!n3){
        return -1;
    }

    int res = 0;
    int nitems = Node_NItems(n3);
    nr_int32 val1, val2, val3;
    for (int i = 0; i < nitems; i++){
        val3 = *((nr_int32*)n3->data + i);
        val2 = *((nr_int32*)n2->data + i);
        val1 = *((nr_int32*)n1->data + i);

        if (val3 != val1 * val2){
            res = -1;
            break;
        }
    }

    Node_Free(n1);
    Node_Free(n2);
    Node_Free(n3);

    return res;
}

static int test_nmath_4(){
    Node *n1, *n2, *n3;
    _NEW_NODE_4x4_INT32(n1);
    if (!n1){
        return -1;
    }

    _NEW_NODE_4x4_FLOAT64(n2);
    if (!n2){
        Node_Free(n1);
        return -1;
    }

    n3 = NMath_Mul(NULL, n1, n2);
    if (!n3){
        return -1;
    }

    int res = 0;
    int nitems = Node_NItems(n3);
    nr_int32 val1;
    nr_float64 val2, val3;
    for (int i = 0; i < nitems; i++){
        val3 = *((nr_float64*)n3->data + i);
        val2 = *((nr_float64*)n2->data + i);
        val1 = *((nr_int32*)n1->data + i);

        if (val3 != (nr_float64)val1 * val2){
            res = -1;
            break;
        }
    }

    Node_Free(n1);
    Node_Free(n2);
    Node_Free(n3);

    return res;
}

static int test_nmath_5(){
    Node *n1, *n2, *n3;
    _NEW_NODE_4x4_INT32(n1);
    if (!n1){
        return -1;
    }

    _NEW_NODE_4x4_INT32(n2);
    if (!n2){
        Node_Free(n1);
        return -1;
    }

    _NEW_NODE_4x4_INT32(n3);
    if (!n3){
        Node_Free(n1);
        Node_Free(n2);
        return -1;
    }

    n3 = NMath_Mul(n3, n1, n2);
    if (!n3){
        return -1;
    }

    int res = 0;
    int nitems = Node_NItems(n3);
    nr_int32 val1, val2, val3;
    for (int i = 0; i < nitems; i++){
        val3 = *((nr_int32*)n3->data + i);
        val2 = *((nr_int32*)n2->data + i);
        val1 = *((nr_int32*)n1->data + i);

        if (val3 != val1 * val2){
            res = -1;
            break;
        }
    }

    Node_Free(n1);
    Node_Free(n2);
    Node_Free(n3);

    return res;
}

static int test_nmath_6(){
    Node *n1, *n2, *n3;
    _NEW_NODE_4x4_INT32(n1);
    if (!n1){
        return -1;
    }

    nr_int32 arr[] = NR_32LIKE(10);
    nr_long shp[] = {4, 4};
    int nd = 2;
    NR_DTYPE dtype = NR_INT32;
    n2 = Node_New(arr, 1, nd, shp, dtype);
    if (!n2){
        Node_Free(n1);
        return -1;
    }

    n3 = NMath_Bge(NULL, n1, n2);
    if (!n3){
        Node_Free(n1);
        Node_Free(n2);
        return -1;
    }

    int res = 0;
    int nitems = Node_NItems(n3);
    nr_bool val3;
    nr_int32 val1, val2;
    for (int i = 0; i < nitems; i++){
        val3 = *((nr_bool*)n3->data + i);
        val2 = *((nr_int32*)n2->data + i);
        val1 = *((nr_int32*)n1->data + i);

        if (val3 != (val1 >= val2)){
            res = -1;
            break;
        }
    }

    Node_Free(n1);
    Node_Free(n2);
    Node_Free(n3);

    return res;
}

static int test_nmath_7(){
    Node *n1, *n2, *n3;
    _NEW_NODE_4x4_INT32(n1);
    if (!n1){
        return -1;
    }
    nr_int32* n1data = (nr_int32*)n1->data;
    n1data[0] = -1;
    n1data[1] = 0;

    nr_int32 arr[] = NR_32ZEROS;
    nr_long shp[] = {4, 4};
    int nd = 2;
    NR_DTYPE dtype = NR_INT32;
    n2 = Node_New(arr, 1, nd, shp, dtype);
    if (!n2){
        Node_Free(n1);
        return -1;
    }

    n3 = NMath_Div(NULL, n1, n2);
    if (!n3){
        Node_Free(n1);
        Node_Free(n2);
        return -1;
    }

    int res = 0;
    int nitems = Node_NItems(n3);
    nr_float64 val1, val2, val3, expval;
    for (int i = 0; i < nitems; i++){
        val3 = *((nr_float64*)n3->data + i);
        val2 = (nr_float64)*((nr_int32*)n2->data + i);
        val1 = (nr_float64)*((nr_int32*)n1->data + i);
        expval = val1 / val2;

        if (isnan(val3) && isnan(expval)){
            continue;
        }

        if (val3 != expval){
            res = -1;
            break;
        }
    }

    Node_Free(n1);
    Node_Free(n2);
    Node_Free(n3);

    return res;
}

void test_nmath(){
    NTEST_RUN_TEST("Nour Math",
    {
        NTEST_ONE_TEST(1, test_nmath_1);
        NTEST_ONE_TEST(2, test_nmath_2);
        NTEST_ONE_TEST(3, test_nmath_3);
        NTEST_ONE_TEST(4, test_nmath_4);
        NTEST_ONE_TEST(5, test_nmath_5);
        NTEST_ONE_TEST(6, test_nmath_6);
        NTEST_ONE_TEST(7, test_nmath_7);
    }
    )
}

#endif