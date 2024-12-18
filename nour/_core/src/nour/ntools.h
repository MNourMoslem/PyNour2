#ifndef NOUR__CORE_SRC_NOUR_NODE_NTOOLS_H
#define NOUR__CORE_SRC_NOUR_NODE_NTOOLS_H

#include "nour/nour.h"

NR_PUBLIC int
NTools_BroadcastStrides(nr_long* a_shape, int a_ndim,
                        nr_long* a_strides, nr_long* src_shape,
                        int src_ndim, nr_long* out_strides);

NR_PUBLIC NR_DTYPE
NTools_BroadcastDtypes(NR_DTYPE a, NR_DTYPE b);

NR_PUBLIC int
NTools_CalculateStrides(int nd, const nr_long* shape,
                        nr_long itemsize, nr_long* _des_strides);

#endif