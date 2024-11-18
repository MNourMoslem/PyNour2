#ifndef NOUR__CORE_INCLUDE__NOUR_NR_ERROR_H
#define NOUR__CORE_INCLUDE__NOUR_NR_ERROR_H

#define NERROR_MAX_STRING_LEN 256

#include "nr_config.h"
#include <stdarg.h>
#include <stdio.h>

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

static NError __NR_NERROR_GLOBAL_ERROR_VAR__= {
    .type = NError_NoError,
    .context = ""
};

NR_PRIVATE void
_NError_TypeAsString(NError_Type type, char* trg_str) {
    switch (type) {
        case NError_NoError:
            strcpy(trg_str, "NoError");
            break;
        case NError_MemoryError:
            strcpy(trg_str, "MemoryError");
            break;
        case NError_TypeError:
            strcpy(trg_str, "TypeError");
            break;
        case NError_IndexError:
            strcpy(trg_str, "IndexError");
            break;
        case NError_ValueError:
            strcpy(trg_str, "ValueError");
            break;
        case NError_IOError:
            strcpy(trg_str, "IOError");
            break;
        case NError_ZeroDivisionError:
            strcpy(trg_str, "ZeroDivisionError");
            break;
        case NError_ImportError:
            strcpy(trg_str, "ImportError");
            break;
        case NError_AttributeError:
            strcpy(trg_str, "AttributeError");
            break;
        case NError_KeyError:
            strcpy(trg_str, "KeyError");
            break;
        case NError_AssertionError:
            strcpy(trg_str, "AssertionError");
            break;
        case NError_RuntimeError:
            strcpy(trg_str, "RuntimeError");
            break;
        case NError_OverflowError:
            strcpy(trg_str, "OverflowError");
            break;
        default:
            strcpy(trg_str, "UnknownError");
            break;
    }
}

NR_HEADER int 
NError_IsError(){
    return __NR_NERROR_GLOBAL_ERROR_VAR__.type != NError_NoError;
}

NR_HEADER void* 
NError_RaiseError(NError_Type type, const char *format, ...) {
    __NR_NERROR_GLOBAL_ERROR_VAR__.type = type;

    va_list args;
    va_start(args, format);

    vsnprintf(__NR_NERROR_GLOBAL_ERROR_VAR__.context, NERROR_MAX_STRING_LEN, format, args);

    va_end(args);

    return NULL;
}

NR_HEADER void* 
NError_RaiseErrorNoContext(NError_Type type){
    __NR_NERROR_GLOBAL_ERROR_VAR__.type = type;
    return NULL;
}

NR_HEADER void 
NError_Print(){
    char type_str[30];
    _NError_TypeAsString(__NR_NERROR_GLOBAL_ERROR_VAR__.type, type_str);
    printf("%s: %s\n", type_str, __NR_NERROR_GLOBAL_ERROR_VAR__.context);
}

NR_HEADER void* NError_RaiseMemoryError() {
    return NError_RaiseErrorNoContext(NError_MemoryError);
}

NR_HEADER void* NError_RaiseTypeError() {
    return NError_RaiseErrorNoContext(NError_TypeError);
}

NR_HEADER void* NError_RaiseIndexError() {
    return NError_RaiseErrorNoContext(NError_IndexError);
}

NR_HEADER void* NError_RaiseValueError() {
    return NError_RaiseErrorNoContext(NError_ValueError);
}

NR_HEADER void* NError_RaiseIOError() {
    return NError_RaiseErrorNoContext(NError_IOError);
}

NR_HEADER void* NError_RaiseZeroDivisionError() {
    return NError_RaiseErrorNoContext(NError_ZeroDivisionError);
}

NR_HEADER void* NError_RaiseImportError() {
    return NError_RaiseErrorNoContext(NError_ImportError);
}

NR_HEADER void* NError_RaiseAttributeError() {
    return NError_RaiseErrorNoContext(NError_AttributeError);
}

NR_HEADER void* NError_RaiseKeyError() {
    return NError_RaiseErrorNoContext(NError_KeyError);
}

NR_HEADER void* NError_RaiseAssertionError() {
    return NError_RaiseErrorNoContext(NError_AssertionError);
}

NR_HEADER void* NError_RaiseRuntimeError() {
    return NError_RaiseErrorNoContext(NError_RuntimeError);
}

NR_HEADER void* NError_RaiseOverflowError() {
    return NError_RaiseErrorNoContext(NError_OverflowError);
}

#endif