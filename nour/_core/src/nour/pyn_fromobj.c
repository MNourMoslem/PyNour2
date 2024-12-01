#include"pyn_fromobj.h"
#include "node_core.h"

typedef struct
{
    int ndim;
    nr_size_t shape[NR_NODE_MAX_NDIM];
    NR_DTYPE dtype;
}_shapeAndDtype;

#define PYN_IS_NUMBER(obj) (PyFloat_Check(obj) |\
                            PyLong_Check(obj)  |\
                            PyBool_Check(obj))

#define PYN_SEQ_LEN(obj) PySequence_Check(obj) ? PySequence_Size(obj):\
                         PyObject_Size(obj)

#define PYN_SEQ_GETITEM(obj, item) PySequence_Check(obj) ? PySequence_GetItem(obj, item):\
                                    PyObject_GetItem(obj, PyLong_FromLong(item))

#define PYN_IS_ITER(obj) (PyObject_HasAttrString(obj, "__len__")\
                          && PyObject_HasAttrString(obj, "__getitem__"))

#define PYN_LONG NR_INT64
#define PYN_FLOAT NR_FLOAT64
#define PYN_BOOL NR_BOOL

#define pyn_float nr_float64
#define pyn_long nr_int64
#define pyn_bool nr_bool

#define PYN_FLOAT_AS_NFLOAT(obj) PyFloat_AsDouble(obj)
#define PYN_LONG_AS_NLONG(obj) PyLong_AsLongLong(obj)
#define PYN_BOOL_AS_NBOOL(obj) (pyn_bool)PyLong_AsLong(obj)

#define PYN_ONLY_NUM_ERR(item) \
    PyErr_Format(PyExc_ValueError,\
        "PyNour node accpets only numerical type objects.",\
        "got %s",\
        (char*)Py_TYPE(item)->tp_name\
    )

#define PYN_CANT_GETITEM \
    PyErr_Format(PyExc_ValueError, \
        "Unexpected error happend while itarting throw array items."\
        "were not able to get the item using __getitem__."\
    )

NR_PRIVATE int
convert_data_block_from_bool2long(Node* node, nr_size_t end){
    pyn_bool* dataptr = node->data;
    
    nr_size_t nitems = Node_NItems(node);
    pyn_long* new_dataptr = malloc(nitems * sizeof(pyn_long));
    if (!new_dataptr){
        PyErr_NoMemory();
        return -1;
    }

    for (nr_size_t i = 0; i < end; i++){
        *(new_dataptr + i) = (pyn_long)*(dataptr + i);
    }

    if (NODE_IS_OWNDATA(node)){
        free(node->data);
    }
    node->data = new_dataptr;
    node->dtype.dtype = PYN_LONG;
    node->dtype.size = NDtype_Size(PYN_LONG);
    return 0;
}

NR_PRIVATE int
convert_data_block_from_bool2float(Node* node, nr_size_t end){
    pyn_bool* dataptr = node->data;
    
    nr_size_t nitems = Node_NItems(node);
    pyn_float* new_dataptr = malloc(nitems * sizeof(pyn_float));
    if (!new_dataptr){
        PyErr_NoMemory();
        return -1;
    }

    for (nr_size_t i = 0; i < end; i++){
        *(new_dataptr + i) = (pyn_float)*(dataptr + i);
    }

    if (NODE_IS_OWNDATA(node)){
        free(node->data);
    }
    node->data = new_dataptr;
    node->dtype.dtype = PYN_FLOAT;
    node->dtype.size = NDtype_Size(PYN_FLOAT);
    return 0;
}

NR_PRIVATE int
convert_data_block_from_long2float(Node* node, nr_size_t end){
    pyn_long* dataptr = node->data;
    
    nr_size_t nitems = Node_NItems(node);
    pyn_float* new_dataptr = malloc(nitems * sizeof(pyn_float));
    if (!new_dataptr){
        PyErr_NoMemory();
        return -1;
    }

    for (nr_size_t i = 0; i < end; i++){
        *(new_dataptr + i) = (pyn_float)*(dataptr + i);
    }

    if (NODE_IS_OWNDATA(node)){
        free(node->data);
    }
    node->data = new_dataptr;
    node->dtype.dtype = PYN_FLOAT;
    node->dtype.size = NDtype_Size(PYN_FLOAT);
    return 0;
}

NR_PRIVATE NR_DTYPE
discover_dtype(PyObject* obj){
    if (PyFloat_Check(obj)){
        return PYN_FLOAT;
    }
    else if (PyBool_Check(obj)){
        return PYN_BOOL;
    }
    else if (PyLong_Check(obj)){
        return PYN_LONG;
    }
    else{
        PYN_ONLY_NUM_ERR(obj);
        return -1;
    }
}

NR_STATIC int
discover_shape_and_dtype_recursive(PyObject *obj, _shapeAndDtype* sad, int current){
    if (current >= NR_NODE_MAX_NDIM){
        PyErr_Format(
            PyExc_ValueError,
            "maximum number of dimensions node could is %i."
            " input object has higher then that",
            NR_NODE_MAX_NDIM
        );
        return -1;
    }
    
    nr_size_t len = PYN_SEQ_LEN(obj);
    sad->shape[current] = len;
    current++;
    int res; 

    PyObject* first = PYN_SEQ_GETITEM(obj, 0);
    if (!first){
        PYN_CANT_GETITEM;
        return -1;
    }
    else if (PYN_IS_ITER(first)){
        res = discover_shape_and_dtype_recursive(first, sad, current);
    }
    else if (PYN_IS_NUMBER(first)){
        NR_DTYPE dtype = discover_dtype(first);
        if (dtype < 0){
            PYN_ONLY_NUM_ERR(first);
            res = -1;
        }
        sad->dtype = dtype;
        sad->ndim = current;
        res = 0;
    }
    else{
        PyErr_Format(
            PyExc_ValueError,
            "input object must contain either numerical(Int, Float, Bool) "
            "or itrable objects (Tuple, Lists, ..). got %s",
            (char*)Py_TYPE(first)->tp_name  
        );
        res = -1;
    }
    Py_DECREF(first);
    return res;
}

NR_STATIC int
discover_shape_and_dtype(PyObject *obj, _shapeAndDtype* sad){
    return discover_shape_and_dtype_recursive(obj, sad, 0);
}

NR_STATIC int
copy_data_from_seq2node_float_first(PyObject* obj, Node* node,
                                    nr_size_t* idx, nr_size_t len, nr_size_t start){
    PyObject* item;
    nr_size_t cidx = *idx;
    nr_size_t step = node->dtype.size;
    pyn_float* dataptr = node->data + cidx * step;

    if (PySequence_Check(obj)){
        for (nr_size_t i = start; i < len; i++){
            item = PySequence_GetItem(obj, i);
            if (!item){
                PYN_CANT_GETITEM;
                return -1;
            }

            if (PyFloat_Check(item)){
                *(dataptr + i)= PYN_FLOAT_AS_NFLOAT(item); 
            }
            else if (PyLong_Check(item) | PyBool_Check(item)){
                *(dataptr + i)= PYN_FLOAT_AS_NFLOAT(PyNumber_Float(item));
            }
            else{
                PYN_ONLY_NUM_ERR(item);
                Py_DECREF(item);
                return -1;
            }
            Py_DECREF(item);
        }
    }
    else{
        for (nr_size_t i = start; i < len; i++){
            item = PyObject_GetItem(obj, PyLong_FromSize_t(i));
            if (!item){
                PYN_CANT_GETITEM;
                return -1;
            }
            if (PyFloat_Check(item)){
                *(dataptr + i)= PYN_FLOAT_AS_NFLOAT(item); 
            }
            else if (PyLong_Check(item) | PyBool_Check(item)){
                *(dataptr + i)= PYN_FLOAT_AS_NFLOAT(PyNumber_Float(item));
            }
            else{
                PYN_ONLY_NUM_ERR(item);
                Py_DECREF(item);
                return -1;
            }
            Py_DECREF(item);
        }
    }

    *idx = cidx + len;
    return 0;
}

NR_STATIC int
copy_data_from_seq2node_int_first(PyObject* obj, Node* node,
                                    nr_size_t* idx, nr_size_t len, nr_size_t start){
    PyObject* item;
    nr_size_t cidx = *idx;
    nr_size_t step = node->dtype.size;
    pyn_long* dataptr = node->data + cidx * step;

    if (PySequence_Check(obj)){
        for (nr_size_t i = start; i < len; i++){
            item = PySequence_GetItem(obj, i);
            if (!item){
                PYN_CANT_GETITEM;
                return -1;
            }

            if (PyLong_Check(item)){
                *(dataptr + i) = PYN_LONG_AS_NLONG(item); 
            }
            else if (PyFloat_Check(item)){
                int res = convert_data_block_from_long2float(node, cidx + i);
                if (res != 0){
                    Py_DECREF(item);
                    return -1;
                }

                Py_DECREF(item);
                return copy_data_from_seq2node_float_first(obj, node, idx, len, i);
            }
            else if (PyBool_Check(item)){
                *(dataptr + i) = (pyn_long)PYN_BOOL_AS_NBOOL(item);
            }
            else{
                PYN_ONLY_NUM_ERR(item);
                Py_DECREF(item);
                return -1;
            }
            Py_DECREF(item);
        }
    }
    else{
        for (nr_size_t i = start; i < len; i++){
            item = PyObject_GetItem(obj, PyLong_FromSize_t(i));
            if (!item){
                PYN_CANT_GETITEM;
                return -1;
            }

            if (PyLong_Check(item)){
                *(dataptr + i) = PYN_LONG_AS_NLONG(item); 
            }
            else if (PyFloat_Check(item)){
                int res = convert_data_block_from_long2float(node, cidx + i);
                if (res != 0){
                    Py_DECREF(item);
                    return -1;
                }

                *idx = cidx + i;
                Py_DECREF(item);
                return copy_data_from_seq2node_float_first(obj, node, idx, len, i);
            }
            else if (PyBool_Check(item)){
                *(dataptr + i) = (pyn_long)PYN_BOOL_AS_NBOOL(item);
            }
            else{
                PYN_ONLY_NUM_ERR(item);
                Py_DECREF(item);
                return -1;
            }
            Py_DECREF(item);
        }
    }

    *idx = cidx + len;
    return 0;
}

NR_STATIC int
copy_data_from_seq2node_bool_first(PyObject* obj, Node* node,
                                    nr_size_t* idx, nr_size_t len, nr_size_t start){
                                            PyObject* item;
    nr_size_t cidx = *idx;
    nr_size_t step = node->dtype.size;
    pyn_bool* dataptr = node->data + cidx * step;

    if (PySequence_Check(obj)){
        for (nr_size_t i = start; i < len; i++){
            item = PySequence_GetItem(obj, i);
            if (!item){
                PyErr_Format(PyExc_ValueError, 
                    "Unexpected error happend while itarting throw array items."
                    "were not able to get the item using __getitem__."
                );
                return -1;
            }

            if (PyBool_Check(item)){
                *(dataptr + i) = PYN_BOOL_AS_NBOOL(item); 
            }
            else if (PyLong_Check(item)){
                int res = convert_data_block_from_bool2long(node, cidx + i);
                if (res != 0){
                    Py_DECREF(item);
                    return -1;
                }
                Py_DECREF(item);
                return copy_data_from_seq2node_int_first(obj, node, idx, len, i);
            }
            else if (PyFloat_Check(item)){
                int res = convert_data_block_from_bool2float(node, cidx + i);
                if (res != 0){
                    Py_DECREF(item);
                    return -1;
                }
                Py_DECREF(item);
                return copy_data_from_seq2node_float_first(obj, node, idx, len, i);
            }
            else{
                PYN_ONLY_NUM_ERR(item);
                Py_DECREF(item);
                return -1;
            }
            Py_DECREF(item);
        }
    }
    else{
        for (nr_size_t i = start; i < len; i++){
            item = PyObject_GetItem(obj, PyLong_FromSize_t(i));
            if (!item){
                return -1;
            }

            if (PyBool_Check(item)){
                *(dataptr + i) = PYN_BOOL_AS_NBOOL(item); 
            }
            else if (PyLong_Check(item)){
                int res = convert_data_block_from_bool2long(node, cidx + i);
                if (res != 0){
                    Py_DECREF(item);
                    return -1;
                }
                *idx = cidx + i;
                Py_DECREF(item);
                return copy_data_from_seq2node_int_first(obj, node, idx, len, i);
            }
            else if (PyFloat_Check(item)){
                int res = convert_data_block_from_bool2float(node, cidx + i);
                if (res != 0){
                    Py_DECREF(item);
                    return -1;
                }
                *idx = cidx + i;
                Py_DECREF(item);
                return copy_data_from_seq2node_float_first(obj, node, idx, len, i);
            }
            else{
                PYN_ONLY_NUM_ERR(item);
                Py_DECREF(item);
                return -1;
            }
            Py_DECREF(item);
        }
    }

    *idx = cidx + len;
    return 0;
}

NR_STATIC int
copy_data_from_seq2node(PyObject* obj, Node* node, int current, nr_size_t* idx){
    nr_size_t len = PYN_SEQ_LEN(obj);
    if (node->shape[current] != len){
        PyErr_Format(PyExc_ValueError, 
            "array is non homogenous at dim %i, expected length %llu, magot %llu",
            current, node->shape[current], len
        );
    
        return -1;
    }

    if (node->dtype.dtype == PYN_LONG){
        return copy_data_from_seq2node_int_first(obj, node, idx, len, 0);
    }
    else if (node->dtype.dtype == PYN_FLOAT){
        return copy_data_from_seq2node_float_first(obj, node, idx, len, 0);
    }
    else if (node->dtype.dtype == PYN_BOOL){
        return copy_data_from_seq2node_bool_first(obj, node, idx, len, 0);
    }
    else{
        return copy_data_from_seq2node_float_first(obj, node, idx, len, 0);
    }
}

NR_STATIC int
loop_throw_seq_and_copy_data_recursive(PyObject* obj, Node* node, int current, nr_size_t* idx){
    PyObject* first = PYN_SEQ_GETITEM(obj, 0);
    if (!first){
        PyErr_Format(PyExc_ValueError, 
            "could not get first item from object at index %i",
            current
        );
        return -1;
    }

    if (PYN_IS_ITER(first)){
        nr_size_t len = PYN_SEQ_LEN(obj);
        current++;
        int res;
        PyObject* item;

        for (nr_size_t i = 0; i < len; i++){
            item = PYN_SEQ_GETITEM(obj, i);
            res = loop_throw_seq_and_copy_data_recursive(item, node, current, idx);
            if (res != 0){
                return -1;
            }
        }

        return 0;
    }
    else if (PYN_IS_NUMBER(first)){
        return copy_data_from_seq2node(obj, node, current, idx);
    }
    else{
        return -1;
    }
}

NR_STATIC int
loop_throw_seq_and_copy_data(PyObject* obj, Node* node){
    nr_size_t idx = 0;
    int res = loop_throw_seq_and_copy_data_recursive(obj, node, 0, &idx);
    return res;
}

NR_PUBLIC int
PyNode_FromArrayLike(PyNode* self, PyObject* array_like){
    _shapeAndDtype sad;
    int res;

    res = discover_shape_and_dtype(array_like, &sad);
    if (res != 0){
        return -1;
    }

    Node* node = Node_NewEmpty(sad.ndim, sad.shape, sad.dtype);
    if (!node){
        return -1;
    }

    res = loop_throw_seq_and_copy_data(array_like, node);
    if (res != 0){
        Node_Free(node);
        return -1;
    }

    self->node = node;
    return 0;
}
