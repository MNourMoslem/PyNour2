#ifndef NOUR__CORE_SRC_NOUR_NERROR_H
#define NOUR__CORE_SRC_NOUR_NERROR_H

#include "nour/nour.h"

extern NError __NR_NERROR_GLOBAL_ERROR_VAR__;

NR_PRIVATE int 
NError_IsError(){
    return __NR_NERROR_GLOBAL_ERROR_VAR__.type != NError_NoError;
}

NR_PUBLIC void*
NError_RaiseError(NError_Type type, const char *format, ...);

NR_PUBLIC void* 
NError_RaiseErrorNoContext(NError_Type type);

NR_PUBLIC void 
NError_Print();

NR_PRIVATE void* NError_RaiseMemoryError() {
    return NError_RaiseErrorNoContext(NError_MemoryError);
}

NR_PRIVATE void* NError_RaiseTypeError() {
    return NError_RaiseErrorNoContext(NError_TypeError);
}

NR_PRIVATE void* NError_RaiseIndexError() {
    return NError_RaiseErrorNoContext(NError_IndexError);
}

NR_PRIVATE void* NError_RaiseValueError() {
    return NError_RaiseErrorNoContext(NError_ValueError);
}

NR_PRIVATE void* NError_RaiseIOError() {
    return NError_RaiseErrorNoContext(NError_IOError);
}

NR_PRIVATE void* NError_RaiseZeroDivisionError() {
    return NError_RaiseErrorNoContext(NError_ZeroDivisionError);
}

NR_PRIVATE void* NError_RaiseImportError() {
    return NError_RaiseErrorNoContext(NError_ImportError);
}

NR_PRIVATE void* NError_RaiseAttributeError() {
    return NError_RaiseErrorNoContext(NError_AttributeError);
}

NR_PRIVATE void* NError_RaiseKeyError() {
    return NError_RaiseErrorNoContext(NError_KeyError);
}

NR_PRIVATE void* NError_RaiseAssertionError() {
    return NError_RaiseErrorNoContext(NError_AssertionError);
}

NR_PRIVATE void* NError_RaiseRuntimeError() {
    return NError_RaiseErrorNoContext(NError_RuntimeError);
}

NR_PRIVATE void* NError_RaiseOverflowError() {
    return NError_RaiseErrorNoContext(NError_OverflowError);
}

#endif