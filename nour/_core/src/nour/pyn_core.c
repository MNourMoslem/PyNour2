#include "pyn_core.h"
#include "node_core.h"
#include <stdlib.h>

NR_PUBLIC PyNode*
PyNode_Create(PyTypeObject* type_obj, Node* node){
    PyNode* pyn = PyObject_New(PyNode, type_obj);
    if (pyn == NULL) {
        PyErr_NoMemory();
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