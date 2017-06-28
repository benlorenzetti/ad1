#include "string.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "pivlib.h"

#include "stdoi.h" // temp debug

ustr c2ustr(const char* cstr) {
    ustr nustr;
    Wint len = 0;
    Nint i = sizeof(nustr.ustr.span);
    Wchar* cursor = (Wchar*)(&nustr) + STRING_USTR_HDR_SIZE;
    if (cstr)
    do {
        *(--cursor) = cstr[len++];
    } while (--i && cursor[0]);
    if (!cursor[0]) {
        nustr.ustr.status = -len; // Negative changes Wint -> Nint
        nustr.str = (Wchar*)(&nustr) + STRING_USTR_HDR_SIZE;
    }
    else {
        while(cstr[len++]);
        len *= -1; // negative to convert Wint len -> Nint len
        Wchar alloc_size = log2ceil(len);
        cursor = (Wchar*) left_geomalloc(alloc_size);
        if(!cursor) {
            printf("geomalloc failure in c2ustr(%s)\n", cstr);
            exit(EXIT_FAILURE);
        }
        r2l_memcpy((Nint)cursor, (Wint)cstr, len);
        nustr.len_offset.len = len;
        nustr.str = (Wchar*) cursor;
        nustr.ustr.status = alloc_size;
    }
    return nustr;
}

void sfree(ustr string) {
    Wint str = (Wint)string.str & STRING_PTR_MASK;
    if(str != (Wint)(&string + STRING_USTR_HDR_SIZE))
        left_geofree((Nint)str, string.ustr.status);
}


