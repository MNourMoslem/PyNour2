#ifndef NOUR__CORE_SRC_NOUR_NODE_CORE_H
#define NOUR__CORE_SRC_NOUR_NODE_CORE_H

#include "nour/nour.h"

NR_PUPLIC Node*
Node_New(void* data, int copy_data, int ndim, nr_size_t* shape, NR_DTYPE dtype);

#endif