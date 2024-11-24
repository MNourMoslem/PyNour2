#ifndef NOUR__CORE_INCLUDE__NOUR_NR_NODE_H
#define NOUR__CORE_INCLUDE__NOUR_NR_NODE_H

#include "nr_types.h"
#include "nr_dtypes.h"
#include <string.h>

typedef enum
{
    NR_CONTIGUOUS_TYPE = 0,
    NR_STRIDED_TYPE,
    NR_CHILD_TYPE,
}nr_narray_type;

#define NR_NODE_C_ORDER 0x1
#define NR_NODE_F_ORDER 0x2
#define NR_NODE_CONTIGUOUS 0x4
#define NR_NODE_STRIDED 0x8
#define NR_NODE_CHILD 0x10
#define NR_NODE_WRITABLE 0x20
#define NR_NODE_SORTED 0x40
#define NR_NODE_OWNDATA 0x80
#define NR_NODE_TRACK 0x100

typedef struct
{
    void* data;
    int ndim;
    nr_size_t* shape;
    nr_size_t* strides;

    NDtype dtype;

    void* base;
    int flags;
    void* op;
}Node;

#define NODE_DATA(node) node->data
#define NODE_DTYPE(node) node->dtype.dtype
#define NODE_ITEMSIZE(node) node->dtype.size
#define NODE_SHAPE(node) node->shape
#define NODE_NDIM(node) node->ndim
#define NODE_STRIDES(node) node->strides

#define NODE_IS_C_ORDER(node) NR_CHKFLG(node->flags, NR_NODE_C_ORDER)
#define NODE_IS_F_ORDER(node) NR_CHKFLG(node->flags, NR_NODE_F_ORDER)
#define NODE_IS_CONTIGUOUS(node) NR_CHKFLG(node->flags, NR_NODE_CONTIGUOUS)
#define NODE_IS_STRIDED(node) NR_CHKFLG(node->flags, NR_NODE_STRIDED)
#define NODE_IS_CHILD(node) NR_CHKFLG(node->flags, NR_NODE_CHILD)
#define NODE_IS_WRITABLE(node) NR_CHKFLG(node->flags, NR_NODE_WRITABLE)
#define NODE_IS_SORTED(node) NR_CHKFLG(node->flags, NR_NODE_SORTED)
#define NODE_IS_OWNDATA(node) NR_CHKFLG(node->flags, NR_NODE_OWNDATA)

NR_STATIC_INLINE nr_size_t
Node_NItems(const Node* node){
    nr_size_t nitems = 1;
    for (int i = 0; i < node->ndim; i++){
        nitems *= node->shape[i];
    }
    return nitems;
}

NR_STATIC_INLINE int
Node_SameShape(const Node* a, const Node* b){
    return a->ndim == b->ndim 
            && memcmp(a->shape, b->shape, sizeof(nr_size_t) * a->ndim) == 0;
}

typedef Node* (*Node2NodeFunc) (Node* , const Node*);

#endif