#include "free.h"

NR_PUBLIC void
Node_Free(Node* node){
    if (node){
        if (NODE_IS_OWNDATA(node)){
            free(node->data);
        }
        if (node->shape) {free(node->shape);}
        if (node->strides) {free(node->strides);}
        free(node);
    }
}