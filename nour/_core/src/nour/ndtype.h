#ifndef NOUR__CORE_SRC_NOUR_NDTYPE_H
#define NOUR__CORE_SRC_NOUR_NDTYPE_H

#include "nour/nour.h"

extern const nr_size_t __NR_NDTYPE_SIZES__[];

NR_PRIVATE nr_size_t
NDtype_Size(NR_DTYPE dtype){
    return __NR_NDTYPE_SIZES__[dtype];
}

#endif