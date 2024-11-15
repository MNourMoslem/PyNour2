#ifndef NOUR__CORE_INCLUDE__NOUR_NR_DTYPES_H
#define NOUR__CORE_INCLUDE__NOUR_NR_DTYPES_H

#include "nr_types.h"

typedef enum{
    NR_BOOL = 0,
    NR_INT8,
    NR_UINT8,
    NR_INT16,
    NR_UINT16,
    NR_INT32,
    NR_UINT32,
    NR_INT64,
    NR_UINT64,
    NR_FLOAT32,
    NR_FLOAT64
}NR_DTYPE;

typedef struct
{
    NR_DTYPE dtype;
    nr_size_t size;
}NDtype;


#endif