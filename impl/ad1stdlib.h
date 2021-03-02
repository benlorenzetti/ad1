#ifndef AD1STDLIB_H
#define AD1STDLIB_H

#include <stdint.h>

typedef uintptr_t Uint;
typedef intptr_t Zint;
typedef uintptr_t Nint;
typedef unsigned char Uchar;
typedef unsigned char Nchar;

typedef struct slice {
  Nint nth;
  Nint zero;
} slice;

typedef struct alloc {
  Nint ptr;
  Nint len;
} alloc;

Uchar log2floor(Uint);
Uchar log2ceil(Nint);
Nint power2N(Uchar);
Uint power2U(Uchar);
Uint bitwise_rotr0(Uint, Nchar);
Nint bitwise_rotr1(Nint, Uchar);
alloc geomalloc(Uchar);
void geofree(alloc);
void print_malloc_metadata();
//   l2l_memcpy(dest_lend, src slice) -> rend of dest
Nint l2l_memcpy(Nint, slice);
//   r2l_memcpy(dest_lend, src, obj_count, obj_size) -> rend of dest
Nint r2l_memcpy(Nint, Nint, Nint, Uint);
Uint r2r_memcpy(Nint, Nint, Nint);

#endif
