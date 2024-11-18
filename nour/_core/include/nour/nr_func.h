#ifndef NOUR__CORE_INCLUDE__NOUR_NR_FUNC_H
#define NOUR__CORE_INCLUDE__NOUR_NR_FUNC_H

#include "./nr_node.h"

typedef struct
{
    Node** nodes;
    Node* out;
    int n_nodes;
    int dim;
    void* extra;
}NFuncArgs;

typedef void (*NFunc) (NFuncArgs*);

#endif