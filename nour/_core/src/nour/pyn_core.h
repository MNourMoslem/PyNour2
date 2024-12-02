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

#define PyNode_NDIM(pyn) (((PyNode*)pyn)->node->ndim)
#define PyNode_SHAPE(pyn) (((PyNode*)pyn)->node->shape)
#define PyNode_STRIDES(pyn) (((PyNode*)pyn)->node->strides)
#define PyNode_DATA(pyn) (((PyNode*)pyn)->node->data)
#define PyNode_FLAGS(pyn) (((PyNode*)pyn)->node->flags)
#define PyNode_ITEMSIZE(pyn) (((PyNode*)pyn)->node->dtype.size)
#define PyNode_NRDTYPE(pyn) (((PyNode*)pyn)->node->dtype.dtype)
#define PyNode_DTYPE(pyn) (((PyNode*)pyn)->node->dtype)
#define PyNode_BASE(pyn) (((PyNode*)pyn)->node->base)

#endif