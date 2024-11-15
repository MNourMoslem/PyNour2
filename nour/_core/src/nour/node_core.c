#include "node_core.h"
#include "./nerror.h"
#include "./ndtype.h"
#include "./free.h"

#include <string.h>


NR_PRIVATE Node*
_Node_NewInit(int ndim, NR_DTYPE dtype){
    Node* node = malloc(sizeof(Node));
    if (!node){
        return NError_RaiseMemoryError();
    }

    if (ndim > NR_NODE_MAX_NDIM){
        free(node);
        return NError_RaiseError(NError_ValueError, "ndim must be less then %i. got %i\n",
                                 NR_NODE_MAX_NDIM, ndim);
    }

    node->ndim = ndim;
    node->dtype.dtype = dtype;
    node->dtype.size = NDtype_Size(dtype);
    node->base = NULL;
    node->flags = 0;
    node->op = NULL;
    node->prefix = NULL;
}

NR_PRIVATE nr_size_t
_Node_NewInitShapeAndStrides(Node* node, nr_size_t* shape){
    nr_size_t len = sizeof(nr_size_t) * node->ndim;
    node->shape = malloc(len);
    if (!node->shape){
        NError_RaiseMemoryError();
        return -1;
    }
    memcpy(node->shape, shape, len);

    node->strides = malloc(len);
    if (!node->strides){
        free(node->shape);
        NError_RaiseMemoryError();
        return -1;
    }

    nr_size_t nitems = 1;
    for (int i = node->ndim-1; i > -1; i--){
        node->strides[i] = nitems * node->dtype.size;
        nitems *= node->shape[i];
    }

    return nitems;
}

NR_PRIVATE int
_Node_NewInitAndCopyData(Node* node, void* data, nr_size_t nitems){
    node->data = malloc(nitems * node->dtype.size);
    if (!node->data){
        NError_RaiseMemoryError();
        return -1;
    }

    memcpy(node->data, data, nitems * node->dtype.size);
    return 0;
}

NR_PUPLIC Node*
Node_New(void* data_block, int copy_data, int ndim, nr_size_t* shape, NR_DTYPE dtype){
    Node* node = _Node_NewInit(ndim, dtype);
    if (!node){
        return NULL;
    }

    nr_size_t nitems = _Node_NewInitShapeAndStrides(node, shape);
    if (nitems < 0){
        free(node);
        return NULL;
    }

    if (copy_data){
        if(_Node_NewInitAndCopyData(node, data_block, nitems) != 0){
            free(node->shape);
            free(node->strides);
            free(node);
            return NULL;
        }
        NR_SETFLG(node->flags, NR_NODE_OWNDATA);
    }
    else{
        node->data = data_block;
    }

    NR_SETFLG(node->flags, (NR_NODE_C_ORDER | NR_NODE_CONTIGUOUS | NR_NODE_WRITABLE));

    return node;
}