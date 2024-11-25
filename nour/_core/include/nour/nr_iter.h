#ifndef NOUR__CORE_INCLUDE__NOUR_NR_ITER_H
#define NOUR__CORE_INCLUDE__NOUR_NR_ITER_H

#include "nr_error.h"
#include "nr_types.h"
#include "nr_dtypes.h"

#define NR_MULTIITER_MAX_NITER 32

#define NITER_MODE_NONE 0
#define NITER_MODE_CONTIGUOUS 1
#define NITER_MODE_STRIDED 2

typedef struct NIter
{
    void* data;
    int nd_m1;
    nr_size_t shape_m1[NR_NODE_MAX_NDIM];
    nr_size_t strides[NR_NODE_MAX_NDIM];
    nr_size_t backstrides[NR_NODE_MAX_NDIM];

    void* current;

    nr_size_t coords[NR_NODE_MAX_NDIM];
    int idx;
    int end;
    nr_size_t step;

    int iter_mode;
}NIter;

#define NIter_ITER(iter_ptr) do { \
        (iter_ptr)->idx = 0; \
        (iter_ptr)->current = (iter_ptr)->data; \
        if ((iter_ptr)->iter_mode == NITER_MODE_CONTIGUOUS){\
            break;\
        }\
        memset((iter_ptr)->coords, 0, \
               ((iter_ptr)->nd_m1 + 1)*sizeof(nr_size_t)); \
} while (0)

#define NIter_NEXT_CONTIGUOUS(iter_ptr) do { \
        (iter_ptr)->idx++;\
        (iter_ptr)->current += (iter_ptr)->step; \
} while (0)

#define NIter_NEXT_STRIDED(iter_ptr) do { \
    (iter_ptr)->idx++;\
    for (int i = (iter_ptr)->nd_m1; i > -1; i--){ \
        if ((iter_ptr)->coords[i] < (iter_ptr)->shape_m1[i]){\
            (iter_ptr)->coords[i]++;\
            (iter_ptr)->current += (iter_ptr)->strides[i];\
            break;\
        }\
        (iter_ptr)->coords[i] = 0;\
        (iter_ptr)->current -= (iter_ptr)->backstrides[i];\
    }\
} while (0)

#define NIter_NEXT(iter_ptr) do { \
        if ((iter_ptr)->iter_mode == NITER_MODE_CONTIGUOUS){\
            NIter_NEXT_CONTIGUOUS((iter_ptr));\
        }\
        else{\
            NIter_NEXT_STRIDED((iter_ptr));\
        }\
} while(0)

#define NIter_NOTDONE(iter_ptr) ((iter_ptr)->idx < (iter_ptr)->end)
#define NIter_ITEM(iter_ptr) ((iter_ptr)->current)

typedef struct
{
    NIter iters[NR_MULTIITER_MAX_NITER];
    int n_iter;

    nr_size_t out_shape[NR_NODE_MAX_NDIM];
    int out_ndim;

    int idx;
    int end;
    void* current[NR_NODE_MAX_NDIM];
}NMultiIter;

#define NMultiIter_ITER(mit_ptr) do {\
    (mit_ptr)->idx = 0;\
    if ((mit_ptr)->n_iter == 2){\
        NIter_ITER((mit_ptr)->iters);\
        NIter_ITER((mit_ptr)->iters + 1);\
    }\
    for (int i = 0; i < (mit_ptr)->n_iter; i++){\
        NIter_ITER((mit_ptr)->iters + i);\
    }\
} while(0)

#define NMultiIter_NEXT(mit_ptr) do {\
    (mit_ptr)->idx++;\
    if ((mit_ptr)->n_iter == 2){\
        NIter_NEXT((mit_ptr)->iters);\
        NIter_NEXT((mit_ptr)->iters + 1);\
    }\
    else{\
        for (int i = 0; i < (mit_ptr)->n_iter; i++){\
            NIter_NEXT((mit_ptr)->iters + i);\
        }\
    }\
} while(0)

#define NMultiIter_NOTDONE(mit_ptr) ((mit_ptr)->idx < (mit_ptr)->end)
#define NMultiIter_ITEM(mit_ptr, i) (NIter_ITEM((mit_ptr)->iters + i))


typedef struct
{
    void* data;
    int nd_m1;
    nr_size_t shape_m1[NR_NODE_MAX_NDIM];
    nr_size_t strides[NR_NODE_MAX_NDIM];
    nr_size_t backstrides[NR_NODE_MAX_NDIM];
    nr_size_t coords[NR_NODE_MAX_NDIM];
    void* current;
    int idx;
    int end;
    int iter_mode;
    nr_size_t step;
    nr_size_t bounds[NR_NODE_MAX_NDIM];

    int widx;
    int wend;
    nr_size_t wstep;
    void *wcurrent;
    nr_size_t wshape_m1[NR_NODE_MAX_NDIM];
    nr_size_t wstrides[NR_NODE_MAX_NDIM];
    nr_size_t wbackstrides[NR_NODE_MAX_NDIM];
    nr_size_t wcoords[NR_NODE_MAX_NDIM];
    int wmode;
}NWindowIter;

#define NWindowIter_ITER(witer_ptr) NIter_ITER(witer_ptr)
#define NWindowIter_NEXT(witer_ptr) NIter_NEXT(witer_ptr)
#define NWindowIter_NOTDONE(witer_ptr) ((witer_ptr)->idx < (witer_ptr)->end)
#define NWindowIter_ITEM(witer_ptr) ((witer_ptr)->current)

#define NWindowIter_ITER_WINDOW(witer_ptr) do{\
    (witer_ptr)->widx = 0; \
    (witer_ptr)->wcurrent = (witer_ptr)->current; \
    if ((witer_ptr)->wmode == NITER_MODE_CONTIGUOUS){\
        break;\
    }\
    memset((witer_ptr)->wcoords, 0, \
            ((witer_ptr)->nd_m1 + 1)*sizeof(nr_size_t)); \
} while (0)

#define NWindowIter_NEXT_WINDOW_CONTIGUOUS(witer_ptr) do { \
        (witer_ptr)->wcurrent += (witer_ptr)->wstep; \
} while (0)

#define NWindowIter_NEXT_WINDOW_STRIDED(witer_ptr) do { \
    for (int i = (witer_ptr)->nd_m1; i > -1; i--){ \
        if ((witer_ptr)->wcoords[i] < (witer_ptr)->wshape_m1[i]){\
            (witer_ptr)->wcoords[i]++;\
            (witer_ptr)->wcurrent += (witer_ptr)->wstrides[i];\
            break;\
        }\
        (witer_ptr)->wcoords[i] = 0;\
        (witer_ptr)->wcurrent -= (witer_ptr)->wbackstrides[i];\
    }\
} while (0)

#define NWindowIter_NEXT_WINDOW(witer_ptr) do { \
        (witer_ptr)->widx++;\
        if ((witer_ptr)->wmode == NITER_MODE_CONTIGUOUS){\
            NWindowIter_NEXT_WINDOW_CONTIGUOUS((witer_ptr));\
        }\
        else{\
            NWindowIter_NEXT_WINDOW_STRIDED((witer_ptr));\
        }\
} while(0)

#define NWindowIter_NOTDONE_WINDOW(witer_ptr) ((witer_ptr)->widx < (witer_ptr)->wend)
#define NWindowIter_ITEM_WINDOW(witer_ptr) ((witer_ptr)->wcurrent)

#endif

