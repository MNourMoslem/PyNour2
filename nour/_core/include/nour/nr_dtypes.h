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

static const nr_size_t __NR_NDTYPE_SIZES__[] = {
    NR_BOOL_SIZE,
    NR_INT8_SIZE,
    NR_UINT8_SIZE,
    NR_INT16_SIZE,
    NR_UINT16_SIZE,
    NR_INT32_SIZE,
    NR_UINT32_SIZE,
    NR_INT64_SIZE,
    NR_UINT64_SIZE,
    NR_FLOAT32_SIZE,
    NR_FLOAT64_SIZE,
};

NR_HEADER nr_size_t
NDtype_Size(NR_DTYPE dtype){
    return __NR_NDTYPE_SIZES__[dtype];
}

#endif