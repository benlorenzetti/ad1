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

typedef struct iter {
  Nint ptr;
  Nint len;
} iter;

Uint slice_eq(slice, slice);
Uint slice_0(slice); // returns T(0) if nth = 0.
Uint alloc_eq(alloc, alloc); // returns T(0)if a = b.
alloc alloc_0();
alloc iter2alloc(iter);
iter alloc2iter(alloc);
Uint iter_eq(iter, iter);
iter iter_0();
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
Nint r2r_memcpy(Nint, slice);
// r2r_memcpy(dest, src) -> returns new src rend
slice slc_copy(slice, slice);
/* slc_copy(dest, src) returns a slice of size <= dest and equal to src size,
 * filled with data from copied from src. Assumes size(dest) >= size(src).
 */
Nint slc_len(slice);


#endif
