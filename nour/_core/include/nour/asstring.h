#ifndef NOUR__CORE_INCLUDE__NOUR_ASSTRING_H
#define NOUR__CORE_INCLUDE__NOUR_ASSTRING_H

#include "nr_types.h"
#include "nr_config.h"

#include <stdio.h>
#include <stdlib.h>

NR_HEADER void
NTools_ShapeAsString(nr_intp* shape, int ndim, char str[]) {
    str[0] = '(';

    int current = 1;

    for (int i = 0; i < ndim; i++) {
        int len = snprintf(str + current, 20, "%llu", shape[i]);
        current += len;

        if (i < ndim - 1) {
            str[current++] = ',';
            str[current++] = ' ';
        }
    }

    str[current++] = ')';
    str[current] = '\0';
}

#endif