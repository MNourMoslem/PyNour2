#include "pyn_core.h"
#include "pyn_fromobj.h"

#define PY_SSIZE_T_CLEAN
#include <Python.h>

NR_STATIC PyObject*
PyNodeType_New(PyTypeObject *type_obj, PyObject *args, PyObject *kwargs){
    return (PyObject*)PyNode_Create(NULL);
}

NR_STATIC int
PyNodeType_Init(PyNode* pyn, PyObject* args, PyObject* kwargs){
    PyObject* array_like;
    if (!PyArg_ParseTuple(args, "O", &array_like)){
        PyErr_SetString(PyExc_ValueError, "i have no idea");
        return -1;
    }

    return PyNode_FromArrayLike(pyn, array_like);
}

NR_STATIC PyObject* PyNodeType_GetItem(PyNode* self, PyObject* index) {
    if (self->node == NULL) {
        PyErr_SetString(PyExc_ValueError, "Data is not initialized");
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
    .tp_flags = Py_TPFLAGS_DEFAULT,
    .tp_new = PyNodeType_New,
    .tp_init = (initproc)PyNodeType_Init,
    .tp_as_mapping = &PyNodeType_as_mapping,
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

    m = PyModule_Create(&nour);
    if (m == NULL)
        return NULL;

    Py_INCREF(&PyNodeType);
    PyModule_AddObject(m, "node", (PyObject*)&PyNodeType);

    return m;
}