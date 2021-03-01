#ifndef AD1STDLIB_H
#define AD1STDLIB_H

#include <stdint.h>

typedef uintptr_t Uint;
typedef intptr_t Zint;
typedef uintptr_t Nint;
typedef unsigned char Uchar;
typedef unsigned char Nchar;

Uchar log2floor(Nint);
Uchar log2ceil(Nint);
Nint power2N(Uchar);
Uint power2U(Uchar);
Uint bitwise_rotr0(Uint, Nchar);
Nint bitwise_rotr1(Nint, Uchar);
Nint geomalloc(Uchar);
void geofree(Nint, Nint); // ptr, length
void print_malloc_metadata();
Nint l2l_memcpy(Nint, Nint, Nint);
Nint r2l_memcpy(Nint, Uint, Uint, Uint);
//   r2l_memcpy(dest, src, obj_count, obj_size) = rend of dest
Uint r2r_memcpy(Uint, Uint, Uint, Uint);

#endif
