#include "pyn_core.h"
#include "node_core.h"

NR_PUBLIC PyNode*
PyNode_Create(Node* node){
    PyNode* pyn = PyObject_New(PyNode, &PyNodeType);
    if (pyn == NULL) {
        PyErr_Format(
            PyExc_MemoryError,
            "can not allocate memory to create node object"
        );
        return NULL;
    }
    pyn->node = node;
    return pyn;
}

NR_PUBLIC void
PyNode_Delete(PyNode* self){
    if (self->node) {
        Node_Free(self->node);
        self->node = NULL;
    }

    Py_TYPE(self)->tp_free((PyObject*)self);
}