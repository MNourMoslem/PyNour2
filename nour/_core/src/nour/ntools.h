#ifndef NOUR__CORE_SRC_NOUR_NODE_NTOOLS_H
#define NOUR__CORE_SRC_NOUR_NODE_NTOOLS_H

#include "nour/nour.h"

NR_PUBLIC int
NTools_BroadcastStrides(nr_size_t* a_shape, int a_ndim,
                        nr_size_t* a_strides, nr_size_t* src_shape,
                        int src_ndim, nr_size_t* out_strides);

NR_PUBLIC NR_DTYPE
NTools_BroadcastDtypes(NR_DTYPE a, NR_DTYPE b);

NR_PUBLIC int
NTools_CalculateStrides(int nd, const nr_size_t* shape,
                        nr_size_t itemsize, nr_size_t* _des_strides);

#endif