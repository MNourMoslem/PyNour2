#ifndef NOUR__CORE_SRC_NOUR_TESTS_NODE_CREATION_H
#define NOUR__CORE_SRC_NOUR_TESTS_NODE_CREATION_H

#include "nour/nour.h"
#include "common.h"
#include "../src/nour/node_core.h"
#include "../src/nour/niter.h"
#include "../src/nour/free.h"
#include <stdio.h>

static int test_node_creation_1(){
    nr_int arr[] = {1, 2, 3, 4, 5, 6};
    nr_size_t shape[] = {2, 3};
    int ndim = 2;
    NR_DTYPE dtype = NR_INT32;

    Node* node = Node_New(arr, 1, ndim, shape, dtype);
    if (!node){
        return -1;
    }

    NIter iter;
    NIter* piter = &iter;

    NIter_FromNode(piter, node, NITER_MODE_STRIDED);

    NIter_ITER(piter);

    int i = 0;
    if (!NIter_NOTDONE(piter)){
        return -1;
    }

    while (NIter_NOTDONE(piter))
    {
        if (*(nr_int*)NIter_ITEM(piter) != arr[i++]){
            return -1;
        }
        NIter_NEXT(piter);
    }

    Node_Free(node);

    return 0;
}

void test_node_creation(){
    NTEST_RUN_TEST("Node Creation",
    {
        NTEST_ONE_TEST(1, test_node_creation_1);
    }
    )
}

#endif