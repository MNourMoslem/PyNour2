#include "pyn_core.h"
#include "pyn_fromobj.h"
#include "pyn_niter.h"
#include "niter.h"
#include "pyn_getset.h"
#include "pyn_methods.h"

#define PY_SSIZE_T_CLEAN
#include <Python.h>

NR_STATIC PyObject*
PyNodeType_New(PyTypeObject *type_obj, PyObject* args, PyObject* kwargs){
    PyObject* array_like;

    static char* kwlist[] = {"array", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "O", kwlist, &array_like)){
        PyErr_SetString(PyExc_ValueError, "could not read the args");
        return NULL;
    }

    PyNode* pyn = PyNode_Create(type_obj, NULL);
    if (!pyn){
        return NULL;
    }

    if (PyNode_FromArrayLike(pyn, array_like) != 0){
        PyNode_Delete((PyObject*)pyn);
        return NULL;
    }
    
    return (PyObject*)pyn;
}

NR_STATIC PyObject*
PyNodeType_Iter(PyObject* self){
    PyObject* args_tuple = PyTuple_Pack(1, self);
    if (args_tuple == NULL) {
        return NULL; 
    }

    PyObject* pit = PyNIterType.tp_new(&PyNIterType, args_tuple, NULL);
    return Py_TYPE(pit)->tp_iter(pit);
}

NR_STATIC PyObject* PyNodeType_GetItem(PyNode* self, PyObject* index) {
    if (self->node == NULL) {
        PyErr_SetString(PyExc_ValueError, "Node is not initialized");
        return NULL;
    }

    nr_int64 idx = PyLong_AsLong(index);
    if (PyErr_Occurred()) {
        return NULL; 
    }

    nr_int64 val = ((nr_int64*)self->node->data)[idx];

    PyObject* item = PyLong_FromLongLong(val);
    Py_INCREF(item);
    return item;
}

static PyMappingMethods PyNodeType_as_mapping = {
    .mp_subscript = (binaryfunc)PyNodeType_GetItem,
};

PyTypeObject PyNodeType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "node",
    .tp_basicsize = sizeof(PyNode),
    .tp_dealloc = (destructor)PyNode_Delete,
    .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
    .tp_new = (newfunc)PyNodeType_New,
    .tp_as_mapping = &PyNodeType_as_mapping,
    .tp_iter = (iternextfunc)PyNodeType_Iter,
    .tp_getset = PyNodeType_GetSetFuncions,
    .tp_methods = PyNodeType_Methods,
};

static PyMethodDef module_methods[] = {
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef nour = {
    .m_base = PyModuleDef_HEAD_INIT,
    .m_name = "nour",
    .m_doc = NULL,
    .m_size = -1, 
    .m_methods = module_methods,
};

PyMODINIT_FUNC PyInit_nour(void) {
    PyObject* m;

    if (PyType_Ready(&PyNodeType) < 0)
        return NULL;

    if (PyType_Ready(&PyNIterType) < 0)
        return NULL;

    m = PyModule_Create(&nour);
    if (m == NULL)
        return NULL;

    Py_INCREF(&PyNodeType);
    PyModule_AddObject(m, "node", (PyObject*)&PyNodeType);
    PyModule_AddObject(m, "niter", (PyObject*)&PyNIterType);

    return m;
}