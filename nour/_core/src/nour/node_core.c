#include <string.h>

#include "node_core.h"
#include "niter.h"
#include "free.h"

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

    return node;
}

NR_PRIVATE nr_size_t
_Node_NewInitShapeAndStrides(Node* node, nr_size_t* shape){
    nr_size_t len = sizeof(nr_size_t) * node->ndim;
    node->shape = malloc(len);
    if (!node->shape){
        NError_RaiseMemoryError();
        return 0;
    }
    memcpy(node->shape, shape, len);

    node->strides = malloc(len);
    if (!node->strides){
        free(node->shape);
        NError_RaiseMemoryError();
        return 0;
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

NR_PUBLIC Node*
Node_New(void* data_block, int copy_data, int ndim, nr_size_t* shape, NR_DTYPE dtype){
    Node* node = _Node_NewInit(ndim, dtype);
    if (!node){
        return NULL;
    }

    nr_size_t nitems = _Node_NewInitShapeAndStrides(node, shape);
    if (nitems == 0){
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

NR_PUBLIC Node*
Node_NewEmpty(int ndim, nr_size_t* shape, NR_DTYPE dtype){
    Node* node = _Node_NewInit(ndim, dtype);
    if (!node){
        return NULL;
    }

    nr_size_t nitems = _Node_NewInitShapeAndStrides(node, shape);
    if(nitems == 0){
        free(node);
        return NULL;
    }

    node->data = malloc(node->dtype.size * nitems);
    if (!node->data){
        free(node->shape);
        free(node->strides);
        free(node);
        return NULL;
    }

    NR_SETFLG(node->flags, (NR_NODE_C_ORDER | NR_NODE_OWNDATA | NR_NODE_CONTIGUOUS | NR_NODE_WRITABLE));

    return node;
}

NR_PUBLIC Node*
Node_Copy(Node* dst, const Node* src){
    if (!dst){
        dst = Node_NewEmpty(src->ndim, src->shape, src->dtype.dtype);
    }
    else if (!Node_SameShape(dst, src)){
        char dshp[30];
        char sshp[30];

        NTools_ShapeAsString(dst->shape, dst->ndim, dshp);
        NTools_ShapeAsString(src->shape, src->ndim, sshp);

        NError_RaiseError(
            NError_ValueError,
            "destenation node has to have the same shape as src node. got %s and %s",
            dshp, sshp
        );

        return NULL;
    }
    else if (dst->dtype.dtype != src->dtype.dtype){
        char dt[30];
        char st[30];

        NDtype_AsStringOnlyType(dst->dtype.dtype, dt);
        NDtype_AsStringOnlyType(src->dtype.dtype, st);
     
        NError_RaiseError(
            NError_ValueError,
            "destenation and src nodes must have the same dtype. got %s and %s",
            dt, st
        );

        return NULL;
    }

    int dcon = NODE_IS_CONTIGUOUS(dst);
    int scon = NODE_IS_CONTIGUOUS(src);

    if (dcon && scon){
        nr_size_t nitems = Node_NItems(dst);
        memcpy(dst->data, src->data, nitems * dst->dtype.size);
    }
    else if (dcon | scon){
        if (dcon){
            nr_size_t bsize = dst->dtype.size;

            NIter it;
            NIter_FromNode(&it, src, NITER_MODE_STRIDED);
            NIter_ITER(&it);
            nr_size_t i = 0;
            while (NIter_NOTDONE(&it))
            {
                memcpy(dst->data + i, NIter_ITEM(&it), bsize);
                i+=bsize;
                NIter_NEXT(&it);
            }
        }
        else{
            nr_size_t bsize = dst->dtype.size;

            NIter it;
            NIter_FromNode(&it, dst, NITER_MODE_STRIDED);
            NIter_ITER(&it);
            nr_size_t i = 0;
            while (NIter_NOTDONE(&it))
            {
                memcpy(NIter_ITEM(&it), src->data + i, bsize);
                i+=bsize;
                NIter_NEXT(&it);
            }
        }
        
    }
    else{
        nr_size_t bsize = dst->dtype.size;

        NIter dit;
        NIter sit;
        NIter_FromNode(&dit, dst, NITER_MODE_STRIDED);
        NIter_FromNode(&sit, src, NITER_MODE_STRIDED);
        NIter_ITER(&dit);
        NIter_ITER(&sit);
        while (NIter_NOTDONE(&sit))
        {
            memcpy(NIter_ITEM(&dit), NIter_ITEM(&sit), bsize);
            NIter_NEXT(&dit);
            NIter_NEXT(&sit);
        }
    }

    return dst;
}