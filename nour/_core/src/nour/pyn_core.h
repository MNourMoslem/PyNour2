#ifndef NOUR__CORE_SRC_NOUR_PYN_CORE_H
#define NOUR__CORE_SRC_NOUR_PYN_CORE_H

#include "nour/nour.h"

#define PY_SSIZE_T_CLEAN
#include <Python.h>

typedef struct {
    PyObject_HEAD
    Node* node;
} PyNode;

extern PyTypeObject PyNodeType;

NR_PUBLIC PyNode*
PyNode_Create(Node* node);

NR_PUBLIC void
PyNode_Delete(PyNode* self);

#endif