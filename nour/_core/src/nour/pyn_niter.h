#ifndef NOUR__CORE_SRC_NOUR_PYN_NITER_H
#define NOUR__CORE_SRC_NOUR_PYN_NITER_H

#include "nour/nour.h"
#include "pyn_core.h"

#define PY_SSIZE_T_CLEAN
#include <Python.h>

typedef struct {
    PyObject_HEAD
    NIter* it;
    PyNode* pyn;
} PyNIter;

extern PyTypeObject PyNIterType;

NR_PUBLIC PyNIter*
PyNIter_FromPyNode(PyNode* pyn);

NR_PUBLIC void
PyNIter_Delete(PyNIter* it);

#endif