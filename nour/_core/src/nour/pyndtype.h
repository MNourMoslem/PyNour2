#ifndef NOUR__CORE_SRC_NOUR_NODE_PYNDTYPE_H
#define NOUR__CORE_SRC_NOUR_NODE_PYNDTYPE_H

#include "nour/nour.h"

#define PY_SSIZE_T_CLEAN
#include <Python.h>

typedef struct
{
    PyObject_HEAD;
    NDtype dtype;
}PyNDtype;

typedef PyTypeObject PyNDtypeType;

extern PyNDtypeType pyndtype;

#endif