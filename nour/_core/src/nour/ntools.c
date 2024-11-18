#include "ntools.h"

NR_PUBLIC int
NTools_BroadcastStrides(nr_size_t* a_shape, int a_ndim,
                        nr_size_t* a_strides, nr_size_t* src_shape,
                        int src_ndim, nr_size_t* out_strides)
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