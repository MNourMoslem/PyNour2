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
    NR_FLOAT64,
    NR_NUM_NUMIRC_DT
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

NR_HEADER void
NDtype_AsString(NR_DTYPE dtype, char dst[]){
    switch (dtype)
    {
    case NR_BOOL:
        strcpy(dst, "NR_BOOL");
        break;
    case NR_INT8:
        strcpy(dst, "NR_INT8");
        break;
    case NR_UINT8:
        strcpy(dst, "NR_UINT8");
        break;
    case NR_INT16:
        strcpy(dst, "NR_INT16");
        break;
    case NR_UINT16:
        strcpy(dst, "NR_UINT16");
        break;
    case NR_INT32:
        strcpy(dst, "NR_INT32");
        break;
    case NR_UINT32:
        strcpy(dst, "NR_UINT32");
        break;
    case NR_INT64:
        strcpy(dst, "NR_INT64");
        break;
    case NR_UINT64:
        strcpy(dst, "NR_UINT64");
        break;
    case NR_FLOAT32:
        strcpy(dst, "NR_FLOAT32");
        break;
    case NR_FLOAT64:
        strcpy(dst, "NR_FLOAT64");
        break;
    default:
        strcpy(dst, "UNKNOWN");
        break;
    }
}

NR_HEADER void
NDtype_AsStringVarType(NR_DTYPE dtype, char dst[]){
    switch (dtype)
    {
    case NR_BOOL:
        strcpy(dst, "nr_bool");
        break;
    case NR_INT8:
        strcpy(dst, "nr_int8");
        break;
    case NR_UINT8:
        strcpy(dst, "nr_uint8");
        break;
    case NR_INT16:
        strcpy(dst, "nr_int16");
        break;
    case NR_UINT16:
        strcpy(dst, "nr_uint16");
        break;
    case NR_INT32:
        strcpy(dst, "nr_int32");
        break;
    case NR_UINT32:
        strcpy(dst, "nr_uint32");
        break;
    case NR_INT64:
        strcpy(dst, "nr_int64");
        break;
    case NR_UINT64:
        strcpy(dst, "nr_uint64");
        break;
    case NR_FLOAT32:
        strcpy(dst, "nr_float32");
        break;
    case NR_FLOAT64:
        strcpy(dst, "nr_float64");
        break;
    default:
        strcpy(dst, "UNKNOWN");
        break;
    }
}

NR_HEADER void
NDtype_AsStringOnlyType(NR_DTYPE dtype, char dst[]){
    switch (dtype)
    {
    case NR_BOOL:
        strcpy(dst, "bool");
        break;
    case NR_INT8:
        strcpy(dst, "int8");
        break;
    case NR_UINT8:
        strcpy(dst, "uint8");
        break;
    case NR_INT16:
        strcpy(dst, "int16");
        break;
    case NR_UINT16:
        strcpy(dst, "uint16");
        break;
    case NR_INT32:
        strcpy(dst, "int32");
        break;
    case NR_UINT32:
        strcpy(dst, "uint32");
        break;
    case NR_INT64:
        strcpy(dst, "int64");
        break;
    case NR_UINT64:
        strcpy(dst, "uint64");
        break;
    case NR_FLOAT32:
        strcpy(dst, "float32");
        break;
    case NR_FLOAT64:
        strcpy(dst, "float64");
        break;
    default:
        strcpy(dst, "UNKNOWN");
        break;
    }
}


#endif