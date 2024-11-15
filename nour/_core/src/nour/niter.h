#ifndef NOUR__CORE_SRC_NOUR_NITER_H
#define NOUR__CORE_SRC_NOUR_NITER_H

#include "nour/nour.h"
#include "nerror.h"
#include "ntools.h"

#define NR_MULTIITER_MAX_NITER 32

#define NITER_MODE_NONE 0
#define NITER_MODE_CONTIGUOUS 1
#define NITER_MODE_STRIDED 2

typedef struct NIter
{
    void* data;
    int ndim;
    nr_size_t* shape;
    nr_size_t* strides;
    nr_size_t* prefix;

    void* current;

    nr_size_t coords[NR_NODE_MAX_NDIM];
    int idx;
    int end;
    int step;

    void* (*next_func) (struct NIter*);

    int iterated;
}NIter;

NR_PUBLIC void
NIter_New(NIter* niter, Node* node, int iter_mode);

NR_PUBLIC void
NIter_FromScratch(NIter* iter ,void* data, int ndim, nr_size_t* shape, nr_size_t* strides, nr_size_t* prefix, int iter_mode);

NR_PRIVATE void
NIter_Iter(NIter* niter){
    niter->idx = -1;
    memset(niter->coords, 0, niter->ndim);
    niter->current = niter->data;
}

NR_PRIVATE void*
NIter_Next(NIter* niter){
    return niter->next_func(niter);
}

NR_PRIVATE void*
NIter_Item(NIter* niter){
    return niter->current;
}

typedef struct
{
    NIter niters[NR_MULTIITER_MAX_NITER];
    int n_niter;

    nr_size_t strides[NR_MULTIITER_MAX_NITER][NR_NODE_MAX_NDIM];

    nr_size_t out_shape[NR_NODE_MAX_NDIM];
    int out_ndim;
}NMultiIter;

NR_PUBLIC int
NMultiIter_New(Node** nodes, int n_nodes, NMultiIter* mit){
    int nd = -1;
    for (int i = 0; i <  n_nodes; i++){
        nd = NR_MAX(nodes[i]->ndim, nd);
    }
    mit->out_ndim = nd;

    int src_node, tmp;
    nr_size_t temp;
    Node* node;
    for (int i = 0; i < n_nodes; i++){
        mit->out_shape[i] = 1;
        for (int j = 0; j < nodes[i]->ndim; j++){
            tmp = i + nodes[i]->ndim - nd;
            if (tmp >= 0){
                temp = node->shape[i];
                if (temp == 1){
                    continue;
                }
                else if (mit->out_shape[i] == temp)
                {   
                    mit->out_shape == temp;
                    src_node = j;
                }
                else{
                    char shape1[100];
                    char shape2[100];

                    NTools_ShapeAsString(nodes[i]->shape, nodes[i]->ndim, shape1);
                    NTools_ShapeAsString(nodes[src_node]->shape, nodes[src_node]->ndim, shape2);

                    NError_RaiseError(NError_ValueError,
                        "objects cannot be broadcast due mismatch at arg %d" 
                        "with shape %s and arg %d with shape %s",
                        nodes[i]->ndim, shape1, nodes[src_node]->ndim, shape2
                    );
                }
            }
        }
    }

    for (int i = 0; i < n_nodes; i++){
        node = nodes[i];
        temp = NTools_BroadcastStrides(node->shape, node->ndim, node->strides, mit->out_shape, mit->out_ndim, mit->strides[i]);
    
        if (temp != 0){
            return -1;
        }
    }

    return 0;
}

#endif