#include "ntools.h"

NR_PUBLIC int
NTools_BroadcastStrides(nr_long* a_shape, int a_ndim,
                        nr_long* a_strides, nr_long* src_shape,
                        int src_ndim, nr_long* out_strides)
{
    if (src_ndim < a_ndim){
        return -1;
    }

    for (int i = 0; i < src_ndim; i++){
        if (src_shape[i] == a_shape[i]){
            out_strides[i] = a_strides[i];
        }
        else if (a_shape[i] == 1){
            out_strides[i] = 0;
        }
        else{
            return -1;
        }
    }

    return 0;
}

NR_PUBLIC NR_DTYPE
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

NR_PUBLIC int
NTools_CalculateStrides(int nd, const nr_long* shape,
                        nr_long itemsize, nr_long* _des_strides)
{
    nr_long nitems = 1;
    if (!shape){
        return -1;
    }

    for (int i = nd-1; i > -1; i--){
        _des_strides[i] = nitems * itemsize;
        nitems *= shape[i];
    }

    return 0;
}