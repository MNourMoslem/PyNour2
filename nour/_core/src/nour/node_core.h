#ifndef NOUR__CORE_SRC_NOUR_NODE_CORE_H
#define NOUR__CORE_SRC_NOUR_NODE_CORE_H

#include "nour/nour.h"
#include "tc_methods.h"
#include "free.h"

NR_PUBLIC Node*
Node_New(void* data, int copy_data, int ndim, nr_size_t* shape, NR_DTYPE dtype);

NR_PUBLIC Node*
Node_NewEmpty(int ndim, nr_size_t* shape, NR_DTYPE dtype);

NR_PUBLIC Node*
Node_Copy(Node* dst, const Node* src);

#endif