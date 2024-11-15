#ifndef NOUR__CORE_SRC_NOUR_NITER_H
#define NOUR__CORE_SRC_NOUR_NITER_H

#include "nour/nour.h"

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

NR_PUPLIC void
NIter_New(NIter* niter, Node* node, int iter_mode);

NR_PUPLIC void
NIter_FromScratch(NIter* iter ,void* data, int ndim, nr_size_t* shape, nr_size_t* strides, nr_size_t* prefix, int iter_mode);

NR_INLINE void
NIter_Iter(NIter* niter){
    niter->idx = 0;
    memset(niter->coords, 0, niter->ndim);
    niter->current = niter->data;
}

NR_INLINE void*
NIter_Next(NIter* niter){
    return niter->next_func(niter);
}

NR_INLINE void*
NIter_Item(NIter* niter){
    return niter->current;
}
#endif