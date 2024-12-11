#include "pyn_methods.h"
#include "pyn_core.h"
#include "shape.h"
#include "pyn_error.h"

/**
 * Wrapper for Node_Reshape
 * Python signature: reshape(self, shape: tuple, /, *, copy: bool = True) -> Node
 */
NR_STATIC PyObject*
PyNodeType_Reshape(PyObject* self, PyObject* args, PyObject* kwargs) {
    PyObject* shape_tuple;
    int copy = 1;  // True by default
    static char* kwlist[] = {"shape", "copy", NULL};
    
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "O!|p", kwlist, 
                                    &PyTuple_Type, &shape_tuple, &copy)) {
        return NULL;
    }

    Py_ssize_t new_ndim = PyTuple_Size(shape_tuple);
    nr_size_t new_shape[NR_NODE_MAX_NDIM];

    for (Py_ssize_t i = 0; i < new_ndim; i++) {
        PyObject* dim = PyTuple_GetItem(shape_tuple, i);
        if (!PyLong_Check(dim)) {
            PyErr_SetString(PyExc_TypeError, "shape dimensions must be integers");
            return NULL;
        }
        new_shape[i] = PyLong_AsSize_t(dim);
    }

    if (copy) {
        PyObject* result = PyNode_Copy(NULL, self);
        if (!result) {
            NError_ToPyError();
            return NULL;
        }

        if (Node_Reshape(PyNode_NODE(result), new_shape, (int)new_ndim) < 0) {
            Py_DECREF(result);
            NError_ToPyError();
            return NULL;
        }
        return result;
    } else {
        // Check if array is contiguous
        if (!(PyNode_FLAGS(self) & NR_NODE_CONTIGUOUS)) {
            PyErr_SetString(PyExc_ValueError, 
                "cannot reshape non-contiguous array in-place. Use copy=True");
            return NULL;
        }
        if (Node_Reshape(PyNode_NODE(self), new_shape, (int)new_ndim) < 0) {
            NError_ToPyError();
            return NULL;
        }
        Py_INCREF(self);
        return self;
    }
}

/**
 * Wrapper for Node_Squeeze
 * Python signature: squeeze(self, /, *, copy: bool = True) -> Node
 */
NR_STATIC PyObject*
PyNodeType_Squeeze(PyObject* self, PyObject* args, PyObject* kwargs) {
    int copy = 1;
    static char* kwlist[] = {"copy", NULL};
    
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "|p", kwlist, &copy)) {
        return NULL;
    }

    if (copy) {
        PyObject* result = PyNode_Copy(NULL, self);
        if (!result) {
            return NULL;
        }
        if (Node_Squeeze(PyNode_NODE(result)) < 0) {
            Py_DECREF(result);
            NError_ToPyError();
            return NULL;
        }
        return result;
    } else {
        if (!(PyNode_FLAGS(self) & NR_NODE_CONTIGUOUS)) {
            PyErr_SetString(PyExc_ValueError, 
                "cannot squeeze non-contiguous array in-place. Use copy=True");
            return NULL;
        }
        if (Node_Squeeze(PyNode_NODE(self)) < 0) {
            NError_ToPyError();
            return NULL;
        }
        Py_INCREF(self);
        return self;
    }
}

/**
 * Wrapper for Node_Transpose
 * Python signature: transpose(self, /, *, copy: bool = True) -> Node
 */
NR_STATIC PyObject*
PyNodeType_Transpose(PyObject* self, PyObject* args, PyObject* kwargs) {
    int copy = 1;
    static char* kwlist[] = {"copy", NULL};
    
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "|p", kwlist, &copy)) {
        return NULL;
    }

    if (copy) {
        PyObject* result = PyNode_Copy(NULL, self);
        if (!result) {
            return NULL;
        }
        if (Node_Transpose(PyNode_NODE(result)) < 0) {
            Py_DECREF(result);
            NError_ToPyError();
            return NULL;
        }
        return result;
    } else {
        if (!(PyNode_FLAGS(self) & NR_NODE_CONTIGUOUS)) {
            PyErr_SetString(PyExc_ValueError, 
                "cannot transpose non-contiguous array in-place. Use copy=True");
            return NULL;
        }
        if (Node_Transpose(PyNode_NODE(self)) < 0) {
            NError_ToPyError();
            return NULL;
        }
        Py_INCREF(self);
        return self;
    }
}

/**
 * Wrapper for Node_SwapAxes
 * Python signature: swapaxes(self, axis1: int, axis2: int, /, *, copy: bool = True) -> Node
 */
NR_STATIC PyObject*
PyNodeType_SwapAxes(PyObject* self, PyObject* args, PyObject* kwargs) {
    int axis1, axis2;
    int copy = 1;
    static char* kwlist[] = {"axis1", "axis2", "copy", NULL};
    
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "ii|p", kwlist, 
                                    &axis1, &axis2, &copy)) {
        return NULL;
    }

    if (copy) {
        PyObject* result = PyNode_Copy(NULL, self);
        if (!result) {
            return NULL;
        }
        if (Node_SwapAxes(PyNode_NODE(result), axis1, axis2) < 0) {
            Py_DECREF(result);
            NError_ToPyError();
            return NULL;
        }
        return result;
    } else {
        if (!(PyNode_FLAGS(self) & NR_NODE_CONTIGUOUS)) {
            PyErr_SetString(PyExc_ValueError, 
                "cannot swap axes of non-contiguous array in-place. Use copy=True");
            return NULL;
        }
        if (Node_SwapAxes(PyNode_NODE(self), axis1, axis2) < 0) {
            NError_ToPyError();
            return NULL;
        }
        Py_INCREF(self);
        return self;
    }
}

/**
 * Wrapper for Node_MatrixTranspose
 * Python signature: matrix_transpose(self, /, *, copy: bool = True) -> Node
 */
NR_STATIC PyObject*
PyNodeType_MatrixTranspose(PyObject* self, PyObject* args, PyObject* kwargs) {
    int copy = 1;
    static char* kwlist[] = {"copy", NULL};
    
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "|p", kwlist, &copy)) {
        return NULL;
    }

    if (copy) {
        PyObject* result = PyNode_Copy(NULL, self);
        if (!result) {
            return NULL;
        }
        if (Node_MatrixTranspose(PyNode_NODE(result)) < 0) {
            Py_DECREF(result);
            NError_ToPyError();
            return NULL;
        }
        return result;
    } else {
        if (!(PyNode_FLAGS(self) & NR_NODE_CONTIGUOUS)) {
            PyErr_SetString(PyExc_ValueError, 
                "cannot transpose non-contiguous matrix in-place. Use copy=True");
            return NULL;
        }
        if (Node_MatrixTranspose(PyNode_NODE(self)) < 0) {
            NError_ToPyError();
            return NULL;
        }
        Py_INCREF(self);
        return self;
    }
}

PyMethodDef PyNodeType_Methods[] = {
    {"reshape", 
     (PyCFunction)PyNodeType_Reshape,
     METH_VARARGS | METH_KEYWORDS,
     "reshape(shape, *, copy=True) -> Node\n\n"
     "Reshape the node to a new shape while maintaining the total number of elements"},
    
    {"squeeze",
     (PyCFunction)PyNodeType_Squeeze,
     METH_VARARGS | METH_KEYWORDS,
     "squeeze(*, copy=True) -> Node\n\n"
     "Remove all dimensions of size 1 from the shape"},
    
    {"transpose",
     (PyCFunction)PyNodeType_Transpose,
     METH_VARARGS | METH_KEYWORDS,
     "transpose(*, copy=True) -> Node\n\n"
     "Reverse the order of dimensions"},
    
    {"swapaxes",
     (PyCFunction)PyNodeType_SwapAxes,
     METH_VARARGS | METH_KEYWORDS,
     "swapaxes(axis1, axis2, *, copy=True) -> Node\n\n"
     "Swap two axes in the node's shape"},
    
    {"matrix_transpose",
     (PyCFunction)PyNodeType_MatrixTranspose,
     METH_VARARGS | METH_KEYWORDS,
     "matrix_transpose(*, copy=True) -> Node\n\n"
     "Transpose a 2D matrix"},
    
    {NULL, NULL, 0, NULL}  // Sentinel
};