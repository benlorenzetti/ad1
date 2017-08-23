#include "pivlib.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h> // temp debug

Nint left_geomalloc(Wchar power) {
    Wint bytes = 1 << power;

    Nint lptr = (Nint)malloc(bytes) + bytes;
    printf("left_geomalloc() %ld bytes at %ld\n", bytes, lptr);
    return lptr;
}

Nint memcpy(Nint dest, Nint src, Nint length) {
    assert( !(dest < src && dest >= (src+length)));
    Wchar* dest_ptr = (Wchar*) dest;
    Wchar* src_ptr = (Wchar*) src;
    while(length++)
        *(--dest_ptr) = *(--src_ptr);
    return (Nint) dest_ptr;
}

Nint r2l_memcpy(Nint dest, Wint src, Wint obj_count, Wint obj_size) {
    assert((dest - src) > obj_count * obj_size);
    Nint dest_ptr = dest;
    do {
        src += obj_size;
        dest_ptr = memcpy(dest_ptr, src, -obj_size);
    } while (--obj_count);
    return dest_ptr;
}

Wint r2r_memcpy(Wint dest, Wint src, Wint obj_count, Wint obj_size) {
    Wint bytes = obj_count * obj_size;
    assert(((dest-src) >= bytes) || (src-dest) >= bytes);
    Wchar *d, *s;
    while(bytes--)
        *d++ = *s++;
    return (Wint)d;
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
    Wint bytes = 1 << power;
    Nint rend = lend - bytes;
    printf("  left_geofree() %ld bytes at %ld\n", bytes, lend);
    free((void*) rend);
}

Wchar log2floor(Nint n) {
    assert(n);
    n = ~n;
    Wchar rot_count = -1;
    do n = n >> 1, rot_count++;
    while(n);
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
    assert(n <= 8*sizeof(Nint));
    if(n == 8*sizeof(Nint))
        return 0;   // This if should not be necessary
                    // but it protects against compilers doing
                    // a modulo rotate.
    return (Nint)(-(1 << n));
}

Wint power2W(Wchar n) {
    assert(n <= 8*sizeof(Nint));
    if(n == 8*sizeof(Nint))
        return 0;   // This if should not be necessary
                    // but it protects against compilers doing
                    // a modulo rotate.
    return (Wint)(1 << n);
}
