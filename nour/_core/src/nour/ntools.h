#ifndef NOUR__CORE_SRC_NOUR_NODE_NTOOLS_H
#define NOUR__CORE_SRC_NOUR_NODE_NTOOLS_H

#include "nour/nour.h"

NR_PUBLIC int
NTools_BroadcastStrides(nr_size_t* a_shape, int a_ndim,
                        nr_size_t* a_strides, nr_size_t* src_shape,
                        int src_ndim, nr_size_t* out_strides);

NR_STATIC_INLINE NR_DTYPE
NTools_BroadcastDtypes(NR_DTYPE a, NR_DTYPE b){
    if (a == b){
        return a;
    }

    NR_DTYPE c = a > b ? a : b;
    if (c <= NR_UINT64){
        if ((c & 1) == 0){
            return NR_FLOAT64;
        }
        return c;
    }
    return c;
}

#endif