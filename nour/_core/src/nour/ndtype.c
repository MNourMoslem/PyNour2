#include "ndtype.h"

static const nr_size_t __NR_NDTYPE_SIZES__[]= {
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

NR_INLINE nr_size_t
NDtype_Size(NR_DTYPE dtype){
    return __NR_NDTYPE_SIZES__[dtype];
}