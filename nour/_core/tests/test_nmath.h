#ifndef NOUR__CORE_SRC_NOUR_TESTS_TEST_NMATH_H
#define NOUR__CORE_SRC_NOUR_TESTS_TEST_NMATH_H

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

    _NEW_NODE_4x4_INT32(n3);
    if (!n3){
        Node_Free(n1);
        Node_Free(n2);
        return -1;
    }

    NR_RMVFLG(n1->flags, NR_NODE_CONTIGUOUS);

    NFuncArgs args;

    Node* in_nodes[] = {n1, n2};
    args.nodes = in_nodes;
    args.out = n3;

    NMath_Add_Int32(&args);

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

    _NEW_NODE_4x4_INT32(n3);
    if (!n3){
        Node_Free(n1);
        Node_Free(n2);
        return -1;
    }

    NFuncArgs args;

    Node* in_nodes[] = {n1, n2};
    args.nodes = in_nodes;
    args.out = n3;

    NMath_Add_Int32(&args);

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

static int test_nmath_3(){
    Node *n1, *n2, *n3;
    _NEW_NODE_4x4_INT32(n1);
    if (!n1){
        return -1;
    }


    nr_int32 __arr[] = {1, 2,                        
                        3, 4};                       
    nr_size_t __shape[] = {4, 1};                    
    int __ndim = 2;                                  
    NR_DTYPE __dtype = NR_INT32;                     
    n2 = Node_New(__arr, 1,                    
                    __ndim,                      
                    __shape,                     
                    __dtype);
    if (!n2){
        Node_Free(n1);
        return -1;
    }
    n2->shape[0] = 4llu;
    n2->shape[1] = 1llu;

    _NEW_NODE_4x4_INT32(n3);
    if (!n3){
        Node_Free(n1);
        Node_Free(n2);
        return -1;
    }

    nr_int32 resarr[] = {2, 3, 4, 5,
                         7, 8, 9, 10,
                         12, 13, 14, 15,
                         17, 18, 19, 20};

    NFuncArgs args;

    Node* in_nodes[] = {n1, n2};
    args.nodes = in_nodes;
    args.out = n3;

    NMath_Add_Int32(&args);

    int res = 0;
    int nitems = Node_NItems(n3);

    nr_size_t val1, val2, val3;
    for (int i = 0; i < nitems; i++){
        val3 = *((nr_int32*)n3->data + i);
        val2 = *((nr_int32*)n2->data + i);
        val1 = *((nr_int32*)n1->data + i);

        if (val3 != resarr[i]){
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
    }
    )
}


#endif