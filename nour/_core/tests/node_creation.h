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
    nr_long shape[] = {2, 3};
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

static int test_node_creation_2(){
    Node *n1, *n2;
    _NEW_NODE_4x4_INT32(n1);
    if (!n1){
        return -1;
    }

    n2 = Node_Copy(NULL, n1);
    if (!n2){
        Node_Free(n1);
        return -1;
    }

    int nitems = (int)Node_NItems(n1);
    if (nitems == 0){
        Node_Free(n1);
        Node_Free(n2);
        return -1;
    }

    int res = 0;
    nr_int32 v1, v2;
    for (int i = 0; i < nitems; i++){
        v1 = *((nr_int32*)(n1->data) + i);
        v2 = *((nr_int32*)(n2->data) + i);

        if (v1 != v2){
            res = -1;
            break;
        }
    }

    Node_Free(n1);
    Node_Free(n2);

    return res;
}

static int test_node_creation_3(){
    Node *n1, *n2;
    _NEW_NODE_4x4_INT32(n1);
    if (!n1){
        return -1;
    }

    nr_int32 arr[] = NR_32ONES;
    nr_long shp[] = {4, 4};
    nr_long nd = 2;
    NR_DTYPE dt = NR_INT32;
    n2 = Node_New(arr, 1, nd, shp, dt);
    if (!n2){
        Node_Free(n1);
        return -1;
    }

    Node_Copy(n2, n1);
    if (!n2){
        Node_Free(n1);
        Node_Free(n2);
        return -1;
    }

    int nitems = (int)Node_NItems(n1);
    if (nitems == 0){
        Node_Free(n1);
        Node_Free(n2);
        return -1;
    }

    int res = 0;
    nr_int32 v1, v2;
    for (int i = 0; i < nitems; i++){
        v1 = *((nr_int32*)(n1->data) + i);
        v2 = *((nr_int32*)(n2->data) + i);

        if (v1 != v2){
            res = -1;
            break;
        }
    }

    Node_Free(n1);
    Node_Free(n2);

    return res;
}

static int test_node_creation_4(){
    Node *n1, *n2;
    _NEW_NODE_4x4_INT32(n1);
    if (!n1){
        return -1;
    }

    nr_int32 arr[] = NR_32ONES;
    nr_long shp[] = {4, 4};
    nr_long nd = 2;
    NR_DTYPE dt = NR_INT32;
    n2 = Node_New(arr, 1, nd, shp, dt);
    if (!n2){
        Node_Free(n1);
        return -1;
    }

    NR_RMVFLG(n1->flags, NR_NODE_CONTIGUOUS);

    Node_Copy(n2, n1);
    if (!n2){
        Node_Free(n1);
        Node_Free(n2);
        return -1;
    }

    int nitems = (int)Node_NItems(n1);
    if (nitems == 0){
        Node_Free(n1);
        Node_Free(n2);
        return -1;
    }

    int res = 0;
    nr_int32 v1, v2;
    for (int i = 0; i < nitems; i++){
        v1 = *((nr_int32*)(n1->data) + i);
        v2 = *((nr_int32*)(n2->data) + i);

        if (v1 != v2){
            res = -1;
            break;
        }
    }

    Node_Free(n1);
    Node_Free(n2);

    return res;
}

static int test_node_creation_5(){
    Node *n1, *n2;
    _NEW_NODE_4x4_INT32(n1);
    if (!n1){
        return -1;
    }

    nr_int32 arr[] = NR_32ONES;
    nr_long shp[] = {4, 4};
    nr_long nd = 2;
    NR_DTYPE dt = NR_INT32;
    n2 = Node_New(arr, 1, nd, shp, dt);
    if (!n2){
        Node_Free(n1);
        return -1;
    }

    NR_RMVFLG(n2->flags, NR_NODE_CONTIGUOUS);

    Node_Copy(n2, n1);
    if (!n2){
        Node_Free(n1);
        Node_Free(n2);
        return -1;
    }

    int nitems = (int)Node_NItems(n1);
    if (nitems == 0){
        Node_Free(n1);
        Node_Free(n2);
        return -1;
    }

    int res = 0;
    nr_int32 v1, v2;
    for (int i = 0; i < nitems; i++){
        v1 = *((nr_int32*)(n1->data) + i);
        v2 = *((nr_int32*)(n2->data) + i);

        if (v1 != v2){
            res = -1;
            break;
        }
    }

    Node_Free(n1);
    Node_Free(n2);

    return res;
}

static int test_node_creation_6(){
    Node *n1, *n2;
    _NEW_NODE_4x4_INT32(n1);
    if (!n1){
        return -1;
    }

    nr_int32 arr[] = NR_32ONES;
    nr_long shp[] = {4, 4};
    nr_long nd = 2;
    NR_DTYPE dt = NR_INT32;
    n2 = Node_New(arr, 1, nd, shp, dt);
    if (!n2){
        Node_Free(n1);
        return -1;
    }

    NR_RMVFLG(n1->flags, NR_NODE_CONTIGUOUS);
    NR_RMVFLG(n2->flags, NR_NODE_CONTIGUOUS);

    Node_Copy(n2, n1);
    if (!n2){
        Node_Free(n1);
        Node_Free(n2);
        return -1;
    }

    int nitems = (int)Node_NItems(n1);
    if (nitems == 0){
        Node_Free(n1);
        Node_Free(n2);
        return -1;
    }

    int res = 0;
    nr_int32 v1, v2;
    for (int i = 0; i < nitems; i++){
        v1 = *((nr_int32*)(n1->data) + i);
        v2 = *((nr_int32*)(n2->data) + i);

        if (v1 != v2){
            res = -1;
            break;
        }
    }

    Node_Free(n1);
    Node_Free(n2);

    return res;
}

static int test_node_creation_7(){
    Node *n1, *n2;
    _NEW_NODE_4x4_INT32(n1);
    if (!n1){
        return -1;
    }

    nr_int8 arr[] = NR_32ONES;
    nr_long shp[] = {4, 4};
    nr_long nd = 2;
    NR_DTYPE dt = NR_INT8;
    n2 = Node_New(arr, 1, nd, shp, dt);
    if (!n2){
        Node_Free(n1);
        return -1;
    }

    int res = Node_Copy(n2, n1) ? -1 : 0;

    Node_Free(n1);
    Node_Free(n2);
    return res;
}

static int test_node_creation_8(){
    Node *n1, *n2;
    _NEW_NODE_4x4_INT32(n1);
    if (!n1){
        return -1;
    }

    _NEW_NODE_2x2_INT32(n2);
    if (!n2){
        Node_Free(n1);
        return -1;
    }

    int res = Node_Copy(n2, n1) ? -1 : 0;

    Node_Free(n1);
    Node_Free(n2);
    return res;
}

void test_node_creation(){
    NTEST_RUN_TEST("Node Creation",
    {
        NTEST_ONE_TEST(1, test_node_creation_1);
        NTEST_ONE_TEST(2, test_node_creation_2);
        NTEST_ONE_TEST(3, test_node_creation_3);
        NTEST_ONE_TEST(4, test_node_creation_4);
        NTEST_ONE_TEST(5, test_node_creation_5);
        NTEST_ONE_TEST(6, test_node_creation_6);
        NTEST_ONE_TEST(7, test_node_creation_7);
        NTEST_ONE_TEST(8, test_node_creation_8);
    }
    )
}

#endif