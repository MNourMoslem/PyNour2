#ifndef NOUR__CORE_SRC_NOUR_NERROR_H
#define NOUR__CORE_SRC_NOUR_NERROR_H

#include "nour/nour.h"

NR_INLINE int 
NError_IsError();

NR_PUPLIC void*
NError_RaiseError(NError_Type type, const char *format, ...);

NR_PUPLIC void* 
NError_RaiseErrorNoContext(NError_Type type);

NR_PUPLIC void 
NError_Print();

NR_INLINE void* NError_RaiseMemoryError() {
    return NError_RaiseErrorNoContext(NError_MemoryError);
}

NR_INLINE void* NError_RaiseTypeError() {
    return NError_RaiseErrorNoContext(NError_TypeError);
}

NR_INLINE void* NError_RaiseIndexError() {
    return NError_RaiseErrorNoContext(NError_IndexError);
}

NR_INLINE void* NError_RaiseValueError() {
    return NError_RaiseErrorNoContext(NError_ValueError);
}

NR_INLINE void* NError_RaiseIOError() {
    return NError_RaiseErrorNoContext(NError_IOError);
}

NR_INLINE void* NError_RaiseZeroDivisionError() {
    return NError_RaiseErrorNoContext(NError_ZeroDivisionError);
}

NR_INLINE void* NError_RaiseImportError() {
    return NError_RaiseErrorNoContext(NError_ImportError);
}

NR_INLINE void* NError_RaiseAttributeError() {
    return NError_RaiseErrorNoContext(NError_AttributeError);
}

NR_INLINE void* NError_RaiseKeyError() {
    return NError_RaiseErrorNoContext(NError_KeyError);
}

NR_INLINE void* NError_RaiseAssertionError() {
    return NError_RaiseErrorNoContext(NError_AssertionError);
}

NR_INLINE void* NError_RaiseRuntimeError() {
    return NError_RaiseErrorNoContext(NError_RuntimeError);
}

NR_INLINE void* NError_RaiseOverflowError() {
    return NError_RaiseErrorNoContext(NError_OverflowError);
}

#endif