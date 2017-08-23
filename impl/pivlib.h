#ifndef PIVLIB_H
#define PIVLIB_H

#include <stdint.h>

typedef uintptr_t Wint;
typedef intptr_t Zint;
typedef uintptr_t Nint;
typedef unsigned char Wchar;

typedef struct rvec {
    Nint nth;
    Nint zero;
} rvec;

Wchar log2floor(Nint);
Wchar log2ceil(Nint);
Nint power2N(Wchar);
Wint power2W(Wchar);
Nint geomalloc(Wchar);
Nint left_geomalloc(Wchar);
void geofree(Nint, Wchar);
void left_geofree(Nint, Wchar);
Nint NfromW(Wint);
Nint memcpy(Nint, Nint, Nint);
Nint r2l_memcpy(Nint, Wint, Wint, Wint);
//   r2l_memcpy(dest, src, obj_count, obj_size) = rend of dest
Wint r2r_memcpy(Wint, Wint, Wint, Wint);

#endif

