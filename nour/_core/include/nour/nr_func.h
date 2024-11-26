#ifndef NOUR__CORE_INCLUDE__NOUR_NR_FUNC_H
#define NOUR__CORE_INCLUDE__NOUR_NR_FUNC_H

#include "./nr_node.h"

typedef struct
{
    Node** nodes;
    Node* out;
    NR_DTYPE outtype;
    int n_nodes;
    int dim;
    void* extra;
}NFuncArgs;

typedef int (*NFunc) (NFuncArgs*);

#endif