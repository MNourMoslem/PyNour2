#include "pyn_getset.h"
#include "nour/nour.h"
#include "pyn_core.h"

NR_STATIC PyObject*
PyNodeType_Ndim(PyObject* self, char* NR_UNUSED(ignored)){
    return PyLong_FromLongLong(PyNode_NDIM(self));
}

NR_STATIC PyObject*
PyNodeType_Shape(PyObject* self, char* NR_UNUSED(ignored)){
    if (PyNode_NDIM(self) <= 0){
        Py_RETURN_NONE;
    }

    PyObject* tuple = PyTuple_New(PyNode_NDIM(self));
    for (int i = 0; i < PyNode_NDIM(self); i++){
        PyTuple_SetItem(tuple, i, PyLong_FromSize_t(PyNode_SHAPE(self)[i]));
    }
    
    return tuple;
}

NR_STATIC PyObject*
PyNodeType_Strides(PyObject* self, char* NR_UNUSED(ignored)){
    if (PyNode_NDIM(self) <= 0){
        Py_RETURN_NONE;
    }

    PyObject* tuple = PyTuple_New(PyNode_NDIM(self));
    for (int i = 0; i < PyNode_NDIM(self); i++){
        PyTuple_SetItem(tuple, i, PyLong_FromSize_t(PyNode_STRIDES(self)[i]));
    }
    
    return tuple;
}

PyGetSetDef PyNodeType_GetSetFuncions[] = {
    {"ndim",
    (getter)PyNodeType_Ndim,
    NULL, NULL, NULL},

    {"shape",
    (getter)PyNodeType_Shape,
    NULL, NULL, NULL},

    {"strides",
    (getter)PyNodeType_Strides,
    NULL, NULL, NULL},
};