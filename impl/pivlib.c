#include "pivlib.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h> // temp debug

Nint left_geomalloc(Wchar power) {
    return (Nint)malloc(1 << power) + (1 << power);
}

Nint memcpy(Nint dest, Nint src, Nint length) {
    assert( !(dest < src && dest >= (src+length)));
    Wchar* dest_ptr = (Wchar*) dest;
    Wchar* src_ptr = (Wchar*) src;
    while(length++)
        *(--dest_ptr) = *(--src_ptr);
    return (Nint) dest_ptr;
}

Nint r2l_memcpy(Nint dest, Wint src, Nint len) {
    assert((dest - src) < len);
    Wchar* dest_ptr = (Wchar*) dest;
    Wchar* src_ptr = (Wchar*) src;
    while(len++)
        *(--dest_ptr) = *(src_ptr++);
    return (Nint) dest_ptr;
}


Nint NfromW(Wint w) {
    return -w;
}

Nint geomalloc(Wchar power) {
    return (Nint)malloc(1 << power);
}

void geofree(Nint rend, Wchar power) {
    free((void*) rend);
}

void left_geofree(Nint lend, Wchar power) {
    lend -= (1 << power);
    free((void*) lend);
}

Wchar log2floor(Nint n) {
    Wint w = -n;
    Wchar rot_count = -1;
    while(w)
        w /= 2, rot_count++;
    return rot_count;
}

Wchar log2ceil(Nint n) {
    Wchar floor = log2floor(n);
    if(n == power2N(floor))
        return floor;
    else
        return 1 + floor;
}

Nint power2N(Wchar n) {
    assert(n < 8*((Wchar)sizeof(Nint)));
    if(n < 0)
        return 0;
    else
        return -(1 << n);
}


