#ifndef NOUR__CORE_SRC_NOUR_PYN_ERROR_H
#define NOUR__CORE_SRC_NOUR_PYN_ERROR_H

#define PY_SSIZE_T_CLEAN
#include <Python.h>

/**
 * Converts the current NError to a Python exception and raises it.
 */
NR_PUBLIC void
NError_ToPyError();

#endif
