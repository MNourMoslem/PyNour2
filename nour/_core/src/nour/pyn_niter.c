#include "pyn_niter.h"
#include "niter.h"

NR_PUBLIC PyNIter* 
PyNIter_FromPyNode(PyNode* pyn) {
    if (pyn == NULL) {
        PyErr_SetString(PyExc_ValueError, "Input PyNode is NULL");
        return NULL;
    }

    PyNIter* pit = PyObject_New(PyNIter, &PyNIterType);
    if (pit == NULL) {
        PyErr_SetString(PyExc_MemoryError, "Cannot allocate memory for PyNIter object");
        return NULL;
    }

    pit->it = malloc(sizeof(NIter));
    if (pit->it == NULL) {
        PyErr_SetString(PyExc_MemoryError, "Cannot allocate memory for NIter structure");
        Py_DECREF(pit);
        return NULL;
    }

    NIter_FromNode(pit->it, pyn->node, NITER_MODE_NONE);

    pit->pyn = pyn;
    Py_INCREF(pyn);
    return pit;
}

NR_PUBLIC void 
PyNIter_Delete(PyNIter* it) {
    if (it) {
        if (it->it) {
            free(it->it);
        }
        Py_XDECREF(it->pyn);
        Py_TYPE(it)->tp_free((PyObject*)it);
    }
}

NR_STATIC PyObject*
PyNIterType_New(NR_UNUSED(PyTypeObject *type), PyObject *args, PyObject *kwargs){
    PyObject* pyn;

    static char* kwlist[] = {"node", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "O", kwlist, &pyn)){
        PyErr_SetString(PyExc_ValueError ,"Did not proived any pynode as input");
        return NULL;
    } 

    if (!PyType_IsSubtype(Py_TYPE(pyn), &PyNodeType)){
        PyErr_Format(PyExc_ValueError ,
        "Expects pynode object as input. got %s",
        (char*)(Py_TYPE(pyn))->tp_name    
        );
        return NULL;    
    }

    return (PyObject*)PyNIter_FromPyNode((PyNode*)pyn);
}

NR_STATIC PyObject*
PyNIterType_Iter(PyObject* it){
    NIter_ITER(((PyNIter*)it)->it);
    return it;
}

NR_STATIC PyObject*
PyNIterType_Next(PyObject* self) {
    PyNIter* pit = (PyNIter*)self;
    NIter* nit = pit->it;
    if (!NIter_NOTDONE(nit)) {
        PyErr_SetString(PyExc_StopIteration, "");
        return NULL;
    }

    void* item = NIter_ITEM(nit);
    PyObject* pyitem = NULL;

    switch (pit->pyn->node->dtype.dtype) {
        case NR_INT8:
            pyitem = PyLong_FromLong(*(nr_int8*)item);
            break;

        case NR_UINT8:
            pyitem = PyLong_FromUnsignedLong(*(nr_uint8*)item);
            break;

        case NR_INT16:
            pyitem = PyLong_FromLong(*(nr_int16*)item);
            break;

        case NR_UINT16:
            pyitem = PyLong_FromUnsignedLong(*(nr_uint16*)item);
            break;

        case NR_INT32:
            pyitem = PyLong_FromLong(*(nr_int32*)item);
            break;

        case NR_UINT32:
            pyitem = PyLong_FromUnsignedLong(*(nr_uint32*)item);
            break;

        case NR_INT64:
            pyitem = PyLong_FromLongLong(*(nr_int64*)item);
            break;

        case NR_UINT64:
            pyitem = PyLong_FromUnsignedLongLong(*(nr_uint64*)item);
            break;

        case NR_BOOL:
            pyitem = PyBool_FromLong(*(nr_bool*)item);
            break;

        case NR_FLOAT32:
            pyitem = PyFloat_FromDouble((double)(*(nr_float32*)item));
            break;

        case NR_FLOAT64:
            pyitem = PyFloat_FromDouble(*(nr_float64*)item);
            break;

        default:
            PyErr_SetString(PyExc_TypeError, "Unsupported data type");
            return NULL;
    }

    NIter_NEXT(nit);

    Py_INCREF(pyitem);
    return pyitem;
}

PyTypeObject PyNIterType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "niter",
    .tp_basicsize = sizeof(PyNIter),
    .tp_dealloc = (destructor)PyNIter_Delete,
    .tp_flags = Py_TPFLAGS_DEFAULT,
    .tp_new = (newfunc)PyNIterType_New,
    .tp_iter = (iternextfunc)PyNIterType_Iter,
    .tp_iternext = (iternextfunc)PyNIterType_Next,
};