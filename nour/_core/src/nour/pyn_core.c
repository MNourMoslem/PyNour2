#include "pyn_core.h"
#include "node_core.h"
#include "pyn_error.h"
#include <stdlib.h>

/**
 * Creates a new PyNode object wrapping a Node structure.
 * 
 * Parameters:
 *   type_obj: Python type object (PyNodeType or a subclass)
 *   node: Pointer to the Node structure to wrap
 * 
 * The function will:
 *   - Allocate new PyNode object using the specified type
 *   - Set the internal Node pointer
 *   - Handle memory allocation failures
 * 
 * Returns:
 *   New PyNode object on success
 *   NULL on failure (with error set)
 */
NR_PUBLIC PyNode*
PyNode_Create(PyTypeObject* type_obj, Node* node) {
    PyNode* pyn = PyObject_New(PyNode, type_obj);
    if (pyn == NULL) {
        PyErr_NoMemory();
        return NULL;
    }
    pyn->node = node;
    return pyn;
}

/**
 * Deallocates a PyNode object and its underlying Node structure.
 * 
 * Parameters:
 *   self: PyNode object to delete
 * 
 * The function will:
 *   - Free the underlying Node structure if it exists
 *   - Print debug information about the deletion
 *   - Call the type's deallocation function
 * 
 * Note:
 *   This function is called by Python's garbage collector
 *   when the reference count reaches zero
 */
NR_PUBLIC void
PyNode_Delete(PyObject* self) {
    if (PyNode_NODE(self)) {
        Node_Free(PyNode_NODE(self));
    }
    printf("deleting %s\n", Py_TYPE(self)->tp_name);
    Py_TYPE(self)->tp_free(self);
}

/**
 * Creates a copy of a PyNode object.
 * If dst is provided, copies data into it. Otherwise creates a new PyNode.
 * 
 * Parameters:
 *   dst: Optional destination PyNode or subclass (can be NULL)
 *   src: Source PyNode or subclass to copy from
 * 
 * Returns:
 *   New or updated PyNode object on success
 *   NULL on failure (with error set)
 */
NR_PUBLIC PyObject*
PyNode_Copy(PyObject* dst, PyObject* src) {
    if (!PyObject_TypeCheck(src, &PyNodeType)) {
        PyErr_SetString(PyExc_TypeError, "source must be a Node object or subclass");
        return NULL;
    }

    Node* dst_node = NULL;
    PyTypeObject* result_type = Py_TYPE(src);  // Use source type by default

    if (dst) {
        if (!PyObject_TypeCheck(dst, &PyNodeType)) {
            PyErr_SetString(PyExc_TypeError, "destination must be a Node object or subclass");
            return NULL;
        }
        dst_node = PyNode_NODE(dst);
        result_type = Py_TYPE(dst);  // Use destination type if provided
    }

    Node* copied = Node_Copy(dst_node, PyNode_NODE(src));
    if (!copied) {
        NError_ToPyError();  // Convert NError to Python exception
        return NULL;
    }

    if (dst) {
        Py_INCREF(dst);
        return dst;
    }

    PyNode* result = PyNode_Create(result_type, copied);
    if (!result) {
        Node_Free(copied);
        NError_ToPyError();  // Convert NError to Python exception
        return NULL;
    }

    return (PyObject*)result;
}