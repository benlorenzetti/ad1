#include <stdint.h>
#include <assert.h>
#include <stdlib.h>


typedef uintptr_t Wint;
typedef intptr_t Zint;
typedef uintptr_t Nint;
typedef unsigned char Wchar;

Wchar log2floor(Nint);
Wchar log2ceil(Nint);
Nint power2(Wchar);
Nint geomalloc(Wchar);
void geofree(Nint, Wchar);
Nint memcpy(Nint, Nint, Nint);
Nint NfromW(Wint);

Nint NfromW(Wint w) {
    return -w;
}

Nint memcpy(Nint dest, Nint src, Nint length) {
    assert( !(dest < src && dest >= (src+length)));
    Wchar* dest_ptr = (Wchar*) dest;
    Wchar* src_ptr = (Wchar*) src;
    while(length++)
        *(--dest_ptr) = *(--src_ptr);
    return dest;
}

Nint geomalloc(Wchar power) {
    return (Nint)malloc(power2(power));
}

void geofree(Nint rend, Wchar power) {
    free((void*) rend);
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
    if(n == power2(floor))
        return floor;
    else
        return 1 + floor;
}

Nint power2(Wchar n) {
    assert(n < 8*((Wchar)sizeof(Nint)));
    if(n < 0)
        return 0;
    else
        return -(1 << n);
}
