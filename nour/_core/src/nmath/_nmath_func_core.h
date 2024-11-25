#include "nour/nour.h"
#include "../src/nour/niter.h"
#include "../src/nour/node_core.h"
#include "../src/nmath/loops.h"
#include <string.h>

#define NMATH_IOTYPE_NONE 0
#define NMATH_IOTYPE_BOOL 1
#define NMATH_IOTYPE_INT 2
#define NMATH_IOTYPE_FLOAT 4

typedef struct
{
    NR_DTYPE intype;
    NR_DTYPE outtype;
}__nmath_iotypes;

NR_PRIVATE void
_CheckDtypes_3Nodes(__nmath_iotypes* iot, Node* c, Node* a, Node* b, int outtype, int intype){
    NR_DTYPE at = a->dtype.dtype;
    NR_DTYPE bt = b->dtype.dtype;
    NR_DTYPE abt = at == bt ? at : NTools_BroadcastDtypes(at, bt);
    NR_DTYPE ct = c->dtype.dtype;
    NR_DTYPE outt = c ? ct : abt;

    if (outtype == NMATH_IOTYPE_NONE){
        iot->outtype = outt;
    }
    else if (outtype == NMATH_IOTYPE_FLOAT){
        iot->outtype = (outt > NR_UINT64) && (outt < NR_NUM_NUMIRC_DT) ? outt : NR_FLOAT64;  
    }
    else if (outtype == NMATH_IOTYPE_BOOL){
        iot->outtype = NR_BOOL;
    }
    else if (outtype == NMATH_IOTYPE_INT){
        iot->outtype = outt < NR_UINT64 ? outt : NR_UINT64;
    }
    else{
        iot->outtype = outt;
    }

    if (intype == NMATH_IOTYPE_NONE){
        iot->intype = outt;
    }
    else if (intype == NMATH_IOTYPE_FLOAT){
        iot->intype = (abt > NR_UINT64) && (abt < NR_NUM_NUMIRC_DT) ? abt : NR_FLOAT64;  
    }
    else if (intype == NMATH_IOTYPE_BOOL){
        iot->intype = NR_BOOL;
    }
    else if (intype == NMATH_IOTYPE_INT){
        iot->intype = abt < NR_UINT64 ? abt : NR_UINT64;
    }
    else{
        iot->intype = outt;
    }
}

NR_PRIVATE void
_IOType_AsString(int iotype, char dst[]){
    if (iotype == NMATH_IOTYPE_FLOAT){
        strcpy(dst, "float");  
    }
    else if (iotype == NMATH_IOTYPE_BOOL){
        strcpy(dst, "boolean");  
    }
    else if (iotype == NMATH_IOTYPE_INT){
        strcpy(dst, "integer");  
    }
    else{
        strcpy(dst, "unknown");  
    }
}

NR_PRIVATE Node*
_NMath_Func_2in1out(Node* c, Node* a, Node* b, NFunc func_list[], int outtype, int intype){
    int copy_a = 0, copy_b = 0;
    int cast_out_to_c = 0;
    __nmath_iotypes iot;
     _CheckDtypes_3Nodes(&iot, c, a, b, outtype, intype);

    if (a->dtype.dtype != iot.intype){
        a = Node_ToType(NULL, a, iot.intype);
        if (!a){
            return NULL;
        }

        copy_a = 1;
    }

    if (b->dtype.dtype != iot.intype){
        b = Node_ToType(NULL, b, iot.intype);
        if (!b){
            if (copy_a){Node_Free(a);}
            return NULL;
        }
        copy_b = 1;
    }

    Node* out;
    if (c && c->dtype.dtype != iot.outtype){
        out = NULL;
        cast_out_to_c = 1;
    }
    else{
        out = c;
    }

    NFunc func = func_list[iot.outtype];

    Node* in[] = {a, b};
    NFuncArgs args = {
        .nodes = in,
        .out = out,
        .n_nodes = 2
    };

    int res = func(&args);

    if (copy_a){
        Node_Free(a);
    }

    if (copy_b){
        Node_Free(b);
    }

    if (cast_out_to_c){
        out = args.out;
        args.out = Node_ToType(c, args.out, c->dtype.dtype);
        Node_Free(out);
    }

    return res != 0 ? NULL : args.out;
}