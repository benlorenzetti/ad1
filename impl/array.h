#ifndef ARRAY_H
#define ARRAY_H

#include "pivlib.h"
#include <assert.h>
#include <stdlib.h>

typedef struct array {
    Nint nth;
    Nint zero;
    Wchar power;
} array;

int array_inspart(array*, Nint, Nint); // vector, ins_ptr, ins_size
int rvec_cmp(const rvec, const rvec, size_t,
             int (*)(const Nint, const Nint)
);

#endif