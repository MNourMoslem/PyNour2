#ifndef NOUR__CORE_INCLUDE__NOUR_NR_FUNC_H
#define NOUR__CORE_INCLUDE__NOUR_NR_FUNC_H

#include "./nr_node.h"

typedef struct
{
    Node** narrays;
    Node* out;
    int n_arr;
    int dim;
}NFuncArgs;

typedef void (*NFunc) (NFuncArgs*);

#endif