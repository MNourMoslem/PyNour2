#ifndef NOUR__CORE_INCLUDE__NOUR_NR_ERROR_H
#define NOUR__CORE_INCLUDE__NOUR_NR_ERROR_H

#define NERROR_MAX_STRING_LEN 256

#include "nr_config.h"

typedef enum {
    NError_NoError,
    NError_MemoryError,
    NError_TypeError,
    NError_IndexError,
    NError_ValueError,
    NError_IOError,
    NError_ZeroDivisionError,
    NError_ImportError,
    NError_AttributeError,
    NError_KeyError,
    NError_AssertionError,
    NError_RuntimeError,
    NError_OverflowError
}NError_Type;

typedef struct
{
    NError_Type type;
    char context[NERROR_MAX_STRING_LEN];
}NError;

static NError __NR_NERROR_GLOBAL_ERROR_VAR__;

#endif