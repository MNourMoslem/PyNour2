#ifndef NOUR__CORE_SRC_NOUR_PYN_FROMOBJ_H
#define NOUR__CORE_SRC_NOUR_PYN_FROMOBJ_H

#include "nour/nour.h"
#include "pyn_core.h"

#define PY_SSIZE_T_CLEAN
#include <Python.h>

NR_PUBLIC int
PyNode_FromArrayLike(PyNode* self, PyObject* args);

#endif