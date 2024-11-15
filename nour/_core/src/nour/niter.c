#include "niter.h"

NR_PRIVATE void*
_NIter_Next_Contiguous(NIter* niter){
    niter->idx++;
    if (niter->idx >= niter->end){
        niter->current = NULL;
    }
    else{
        niter->current = niter->data + niter->step * niter->idx;
    }
    return niter->current;
}

NR_PRIVATE void*
_NIter_Next_Strided(NIter* niter){
    if (niter->current){
        for (int i = niter->ndim-1; i > -1; i--){
            niter->current = niter->data + (niter->strides[i] * niter->coords[i]);
            niter->coords[i]++;
            if (niter->coords[i] >= niter->shape[i]){
                niter->coords[i] = 0;
            }
            else{
                return niter->current;
            } 
        }
        niter->current = NULL;
    }
    return NULL;
}

NR_PRIVATE void*
_NIter_Next_Child(NIter* niter){
    if (niter->current){
        for (int i = niter->ndim-1; i > -1; i--){
            niter->current = niter->data + (niter->strides[i] * (niter->coords[i] + niter->prefix[i]));
            niter->coords[i]++;
            if (niter->coords[i] >= niter->shape[i]){
                niter->coords[i] = 0;
            }
            else{
                return niter->current;
            } 
        }
        niter->current = NULL;
    }
    return NULL;
}

NR_PUBLIC void
NIter_New(NIter* niter, Node* node, int iter_mode){
    if (iter_mode == NITER_MODE_NONE){
        if (NODE_IS_CONTIGUOUS(node)){
            iter_mode = NITER_MODE_CONTIGUOUS;
        }
        else{
            iter_mode = NITER_MODE_STRIDED;
        }
    }

    NIter_FromScratch(niter, node->data, node->ndim,
                     node->shape, node->strides, node->prefix, iter_mode);
}

NR_PUBLIC void
NIter_FromScratch(NIter* niter ,void* data, int ndim, nr_size_t* shape,
                 nr_size_t* strides, nr_size_t* prefix, int iter_mode)
{
    niter->data = data;
    niter->ndim = ndim;
    niter->shape = shape;
    niter->strides = strides;
    niter->prefix = prefix;

    niter->step = strides[ndim - 1];
    niter->end = Node_NItems(ndim, shape);
    niter->idx = niter->end;

    if (iter_mode == NITER_MODE_CONTIGUOUS){
        niter->next_func = _NIter_Next_Contiguous;
    }
    else{
        if (prefix){
            niter->next_func = _NIter_Next_Child;
        }
        else{
            niter->next_func = _NIter_Next_Strided;
        }
    }
}