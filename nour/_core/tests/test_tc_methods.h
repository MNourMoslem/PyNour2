#ifndef NOUR__CORE_SRC_NOUR_TESTS_TEST_TC_METHODS_H
#define NOUR__CORE_SRC_NOUR_TESTS_TEST_TC_METHODS_H

#include "nour/nour.h"
#include "common.h"
#include "../src/nour/niter.h"
#include "../src/nour/node_core.h"
#include "../src/nour/free.h"
#include "../src/nour/nmath.h"

// #define TEST_TC_METHOD_FUNCTION(st, dt) 

static int test_tc_methods_1(){
    int res = 0;

    Node *n1, *n2;
    nr_int32 arr[] = NR_32ONES;
    nr_size_t shp[] = {16};
    int nd = 1;
    NR_DTYPE dt = NR_INT32;
    n1 = Node_New(arr, 1, nd, shp, dt);
    if (!n1){
        return -1;
    }

    n2 = Node_ToType(NULL, n1, NR_FLOAT64);
    if (!n2){
        res = -1;
    }

    int nitems = (int)Node_NItems(n1);
    nr_int32 v1;
    nr_float64 v2;
    for (int i = 0; i < nitems; i++){
        v1 = *((nr_int32*)n1->data + i);
        v2 = *((nr_float64*)n2->data + i);
        if ((nr_float64)v1 != v2){
            res = -1;
            break;
        }
    }

    Node_Free(n1);
    Node_Free(n2);

    return res;
}

void test_tc_methods(){
    NTEST_RUN_TEST("Type Conversion Methods",
    {
        NTEST_ONE_TEST(1, test_tc_methods_1);
    }
    )
}


#endif