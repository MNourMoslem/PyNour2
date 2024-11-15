#ifndef NOUR__CORE_INCLUDE__NOUR_NR_TYPES_H
#define NOUR__CORE_INCLUDE__NOUR_NR_TYPES_H

#include "./nr_config.h"

#include <stdlib.h>
#include <string.h>

#define NR_SETFLG(x, flag) (x |= flag)
#define NR_RMVFLG(x, flag) (x &= ~flag)
#define NR_CHKFLG(x, flag) ((x & flag) == flag)
#define NR_CHKUNI(x, flag) ((x & flag) != 0)

#define NR_BOOL_SIZE 1
#define NR_INT8_SIZE 1
#define NR_UINT8_SIZE 1
#define NR_INT16_SIZE 2
#define NR_UINT16_SIZE 2
#define NR_INT32_SIZE 4
#define NR_UINT32_SIZE 4
#define NR_INT64_SIZE 8
#define NR_UINT64_SIZE 8
#define NR_FLOAT32_SIZE 4
#define NR_FLOAT64_SIZE 8

typedef unsigned char nr_byte;
typedef char nr_char;
typedef unsigned char nr_uint8;
typedef char nr_int8;
typedef unsigned short nr_uint16;
typedef short nr_int16;
typedef unsigned int nr_uint32;
typedef int nr_int32;
typedef unsigned long long nr_uint64;
typedef long long nr_int64;
typedef float nr_float32;
typedef double nr_float64;

typedef nr_int32 nr_int;
typedef nr_float32 nr_float;
typedef nr_float64 nr_double;

typedef size_t nr_size_t;

#define NR_MAX_INT8 127
#define NR_MIN_INT8 -128
#define NR_MAX_UINT8 255
#define NR_MIN_UINT8 0
#define NR_MAX_INT16 32767
#define NR_MIN_INT16 -32768
#define NR_MAX_UINT16 65535
#define NR_MIN_UINT16 0
#define NR_MAX_INT32 2147483647
#define NR_MIN_INT32 -2147483648
#define NR_MAX_UINT32 4294967295u
#define NR_MIN_UINT32 0
#define NR_MAX_INT64 9223372036854775807LL
#define NR_MIN_INT64 -9223372036854775808LL
#define NR_MAX_UINT64 18446744073709551615ULL
#define NR_MIN_UINT64 0

typedef unsigned char nr_bool;
#define NR_FALSE 0
#define NR_TRUE 0

NR_PRIVATE int
NR_IsSameShape(nr_size_t* shape_a, nr_size_t* shape_b, int ndim){
    return memcmp(shape_a, shape_b, sizeof(nr_size_t) * ndim) == 0;
}

#endif