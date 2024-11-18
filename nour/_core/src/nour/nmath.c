#include "nmath.h"
#include "niter.h"

NR_PUBLIC int
NMath_Add_Int32(NFuncArgs* args){
    Node* n1 = args->nodes[0];
    Node* n2 = args->nodes[1];
    Node* out = args->out;

    int ss = Node_SameShape(n1, n2);
    if (NR_CHKFLG((n1->flags & n2->flags), NR_NODE_CONTIGUOUS) && ss) 
        {
        int nitems = Node_NItems(n1);
        for (int i = 0; i < nitems; i++){
            *((nr_int32*)out->data + i) = *((nr_int32*)n1->data + i) + *((nr_int32*)n2->data + i);
        }
    }
    else if (ss){
        if (NR_CHKFLG((n1->flags | n2->flags), NR_NODE_CONTIGUOUS)){
            Node* con_n = NODE_IS_CONTIGUOUS(n1) ? n1 : n2;
            Node* str_n = NODE_IS_CONTIGUOUS(n1) ? n2 : n1;
            NIter it;
            NIter_FromNode(&it, str_n, NITER_MODE_STRIDED);

            int i = 0;
            NIter_ITER(&it);
            while (NIter_NOTDONE(&it))
            {
                *((nr_int32*)out->data + i) = *(nr_int32*)NIter_ITEM(&it) + *((nr_int32*)con_n->data + i);

                NIter_NEXT(&it);
                i++;
            }   
        }
        else{
            NIter it1, it2;
            NIter_FromNode(&it1, n1, NITER_MODE_NONE);
            NIter_FromNode(&it2, n2, NITER_MODE_NONE);

            int i = 0;

            NIter_ITER(&it1);
            NIter_ITER(&it2);
            while (NIter_NOTDONE(&it1))
            {
                *((nr_int32*)out->data + i) = *(nr_int32*)NIter_ITEM(&it1) + *(nr_int32*)NIter_ITEM(&it2);

                NIter_NEXT(&it1);
                NIter_NEXT(&it2);
                i++;
            }
        }
    }
    else{
        NMultiIter mit;
        if (NMultiIter_New(args->nodes, 2, &mit) != 0){
            return -1;
        }

        int i;
        NMultiIter_ITER(&mit);
        while (NMultiIter_NOTDONE(&mit))
        {
            *((nr_int32*)out->data + i) = *(nr_int32*)NMultiIter_ITEM(&mit, 0)
                                         + *(nr_int32*)NMultiIter_ITEM(&mit, 1);
        
            i++;
            NMultiIter_NEXT(&mit);
        }
    }
    return 0;
}