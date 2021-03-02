#include "ad1stdlib.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h> // temp debug

typedef struct malloc_list {
  struct malloc_list* next;
  Nint actual_ptr;
  Nint actual_len;
  Nint revealed_ptr;
} malloc_list;

malloc_list* malloc_metadata;

void print_malloc_metadata() {
  malloc_list* ptr = malloc_metadata;
  int index = 0;
  while(ptr) {
    printf("Allocation %d:\n", ++index);
    printf("\tmalloc ptr:    %20u\n", -ptr->actual_ptr);
    printf("\tmalloc len:    %20u\n", -ptr->actual_len);
    printf("\tgeomalloc ptr: %20u\n", -ptr->revealed_ptr);
    ptr=ptr->next;
  }
}

alloc geomalloc(Uchar power) {
    Nint malloc_ptr = (Nint) malloc(1 << power);
    alloc r = {malloc_ptr, power2N(power)};
//    Nint rend = malloc_ptr;
//    Nint len = -(1 << power);
    Nint power_end = r.len & r.ptr;
    // Check the allocation is correctly aligned by power of 2
    if(malloc_ptr != power_end) {
      // Try to globally shift malloc to a power of two
      Nint left_gap = r.len - (power_end - r.ptr);
      malloc_ptr = (Nint) realloc((void*)r.ptr, -(r.len + left_gap));
      if(malloc_ptr == r.ptr) {
        r.ptr = power_end - r.len;
        r.len = r.len + left_gap; // warning: this alloc no longer power of 2
      }
      else {
        // Just get this allocation done
        malloc_ptr = (Nint) realloc((void*)malloc_ptr, 1 << (power+1));
        power_end = r.len & malloc_ptr;
        r.ptr = power_end - r.len;
        r.len = power2N(power+1);
      }
    }
    // Save metadata for malloc implementations that don't align on 2^u
    malloc_list* new_metadata = malloc(sizeof(malloc_list));
    new_metadata->next = malloc_metadata;
    new_metadata->actual_ptr = malloc_ptr;
    new_metadata->actual_len = r.len;
    new_metadata->revealed_ptr = r.ptr;
    malloc_metadata = new_metadata;
    r.len = power2N(power); // revealed len
    return r;
}

void geofree(alloc a) {
  malloc_list* ptr = malloc_metadata;
  malloc_list* prev = 0;
  assert(ptr);
  a.ptr = a.ptr & a.len;
  if (ptr->revealed_ptr == a.ptr)
    malloc_metadata = ptr->next;
  else {
    do {
      prev = ptr;
      ptr = ptr->next;
      assert(ptr);
    } while (ptr->revealed_ptr != a.ptr);
    prev->next = ptr->next;
  }
  assert(ptr->actual_len <= a.len || ptr->actual_len >= 2*a.len);
  free((void*) ptr->actual_ptr);
  free((void*) ptr);
}

Nint l2l_memcpy(Nint dest, slice src) {
  Nint len = src.nth - src.zero;
  Nint dest_rend = dest + len;
  assert(dest_rend >= src.zero || src.nth > dest); // no alias
  memcpy(dest_rend, src.nth, -len);
  return dest_rend;
}

Nint r2l_memcpy(Nint dest, Nint src, Nint obj_count, Uint obj_size) {
    assert(obj_count);
    assert((src - dest) <= 2 * obj_count * obj_size);
    do {
        dest -= obj_size;
        memcpy(dest, src, obj_size);
        src += obj_size;
    } while (++obj_count);
    return dest;
}

Nint r2r_memcpy(Nint dest, Nint src, Nint length) {
    assert(dest - src <= length || src - dest <= length); // no alias
    memcpy((void*)dest, (void*)src, -length);
    return dest;
}

Uint bitwise_rotr0(Uint u, Nchar r) { return u >> (-r); }
Nint bitwise_rotr1(Nint n, Uchar r) {
  Nint mask = ((!r) ? 0 : (-1) << (8*sizeof(Nint)-r));
  return mask | n >> r;
}

Uchar log2floor(Uint u) {
    assert(u);
    Nchar test_digit = -1;
    while(bitwise_rotr0(u, test_digit))
      --test_digit;
    return ~test_digit;
}

Uchar log2ceil(Nint n) {
    Uchar test_digit = 0;
    while(~bitwise_rotr1(n, test_digit))
      ++test_digit;
    return test_digit;
}

Nint power2N(Uchar n) {
    assert(n <= 8*sizeof(Nint));
    if(n == 8*sizeof(Nint))
        return 0;   // This if should not be necessary
                    // but it protects against compilers doing
                    // a modulo rotate.
    return (Nint)(-(1 << n));
}

Uint power2U(Uchar n) {
    assert(n <= 8*sizeof(Nint));
    if(n == 8*sizeof(Nint))
        return 0;   // This if should not be necessary
                    // but it protects against compilers doing
                    // a modulo rotate.
    return (Uint)(1 << n);
}
