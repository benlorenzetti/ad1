#ifndef ARRAY_H
#define ARRAY_H

#include "pivlib.h"
#include <assert.h>
#include <stdlib.h>

struct array {
    Nint nth;
    Nint zero;
    Wchar power;
};

typedef union {
    struct array array;
    struct rvec rvec;
} array;

#define ARRAY_INIT {0,0,8*sizeof(Nint)}

rvec array_partback(struct array*, Nint); // vector, pushback size
int array_inspart(struct array*, Nint, Nint);
                // vector, ins_ptr, ins_size
int rvec_cmp(const rvec, const rvec, size_t,
             int (*)(const Nint, const Nint)
);
rvec array_rvec_bsearch(const void *,   // key obj
                        rvec,           // array to search
                        Nint,           // obj size
                        int (*)(const Nint, const Nint) // compare f()
);
Nint array_rvec_lsearch(const void *,   // key obj
                        rvec,           // cont. row vec to search
                        Nint,           // obj size
                        int (*)(const Nint, const Nint) // compare f()
);

#endif
