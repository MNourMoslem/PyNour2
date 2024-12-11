#include "pyn_error.h"
#include "nr_error.h"
#include <Python.h>

/**
 * Converts the current NError to a Python exception and raises it.
 * 
 * This function maps NError types to corresponding Python exceptions
 * and raises the exception with the error message from NError.
 */
NR_PUBLIC void
NError_ToPyError() {
    if (!NError_IsError()) {
        return;  // No error to convert
    }

    NError_Type type = __NR_NERROR_GLOBAL_ERROR_VAR__.type;
    const char* message = __NR_NERROR_GLOBAL_ERROR_VAR__.context;

    PyObject* py_exception = NULL;

    switch (type) {
        case NError_MemoryError:
            py_exception = PyExc_MemoryError;
            break;
        case NError_TypeError:
            py_exception = PyExc_TypeError;
            break;
        case NError_IndexError:
            py_exception = PyExc_IndexError;
            break;
        case NError_ValueError:
            py_exception = PyExc_ValueError;
            break;
        case NError_IOError:
            py_exception = PyExc_IOError;
            break;
        case NError_ZeroDivisionError:
            py_exception = PyExc_ZeroDivisionError;
            break;
        case NError_ImportError:
            py_exception = PyExc_ImportError;
            break;
        case NError_AttributeError:
            py_exception = PyExc_AttributeError;
            break;
        case NError_KeyError:
            py_exception = PyExc_KeyError;
            break;
        case NError_AssertionError:
            py_exception = PyExc_AssertionError;
            break;
        case NError_RuntimeError:
            py_exception = PyExc_RuntimeError;
            break;
        case NError_OverflowError:
            py_exception = PyExc_OverflowError;
            break;
        default:
            py_exception = PyExc_RuntimeError;  // Default to RuntimeError
            break;
    }

    PyErr_SetString(py_exception, message);
}
