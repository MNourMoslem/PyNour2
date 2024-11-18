#ifndef NOUR__CORE_SRC_NOUR_NITER_H
#define NOUR__CORE_SRC_NOUR_NITER_H

#include "nour/nour.h"
#include "ntools.h"

#define NR_MULTIITER_MAX_NITER 32

NR_PUBLIC void
NIter_FromNode(NIter* niter, Node* node, int iter_mode);

NR_PUBLIC void
NIter_New(NIter* iter ,void* data, int ndim, nr_size_t* shape, nr_size_t* strides, int iter_mode);

NR_PUBLIC int
NMultiIter_New(Node** nodes, int n_nodes, NMultiIter* mit);

NR_PUBLIC int
NWindowIter_New(Node* node, NWindowIter* wit, nr_size_t* window_dims,
                 nr_size_t* strides_factor, nr_size_t* dilation);

#endif