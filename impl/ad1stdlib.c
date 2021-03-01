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

Nint geomalloc(Uchar power) {
    Nint malloc_ptr = (Nint) malloc(1 << power);
    Nint rend = malloc_ptr;
    Nint len = -(1 << power);
    Nint power_end = len & malloc_ptr;
    // Check the allocation is correctly aligned by power of 2
    if(malloc_ptr != power_end) {
      // Try to globally shift malloc to a power of two
      Nint left_gap = len - (power_end - malloc_ptr);
      Nint old_location = malloc_ptr;
      malloc_ptr = (Nint) realloc((void*)malloc_ptr, -(len + left_gap));
      if(malloc_ptr == old_location) {
        power_end = len & malloc_ptr;
        rend = power_end - len;
        len = len + left_gap;
      }
      else {
        // Just get this allocation done
        malloc_ptr = (Nint) realloc((void*)malloc_ptr, 1 << (power+1));
        power_end = len & malloc_ptr;
        rend = power_end - len;
        len = -(1 << (power+1));
      }
    }
    // Save metadata for malloc implementations that don't align on 2^u
    malloc_list* new_metadata = malloc(sizeof(malloc_list));
    new_metadata->next = malloc_metadata;
    new_metadata->actual_ptr = malloc_ptr;
    new_metadata->actual_len = len;
    new_metadata->revealed_ptr = rend;
    malloc_metadata = new_metadata;
    return rend;
}

void geofree(Nint rend, Nint length) {
  malloc_list* ptr = malloc_metadata;
  malloc_list* prev = 0;
  if (!ptr) {
    printf("ERROR GEOFREE\n");
    exit(0);
  }
  if (ptr->revealed_ptr == rend)
    malloc_metadata = ptr->next;
  else {
    do {
      prev = ptr;
      ptr = ptr->next;
      if (!ptr) {
        printf("ERROR GEOFREE\n");
        exit(0);
      }
    } while (ptr->revealed_ptr != rend);
    prev->next = ptr->next;
  }
  assert(ptr->actual_len == length || ptr->actual_len == 2*length);
  free((void*) ptr->actual_ptr);
  free((void*) ptr);
}

Nint l2l_memcpy(Nint dest, Nint src, Nint length) {
    assert( !(dest < src && dest >= (src+length)));
    Uchar* dest_ptr = (Uchar*) dest;
    Uchar* src_ptr = (Uchar*) src;
    while(length++)
        *(--dest_ptr) = *(--src_ptr);
    return (Nint) dest_ptr;
}

Nint r2l_memcpy(Nint dest, Uint src, Uint obj_count, Uint obj_size) {
    assert((dest - src) > obj_count * obj_size);
    Nint dest_ptr = dest;
    do {
        src += obj_size;
        dest_ptr = memcpy(dest_ptr, src, -obj_size);
    } while (--obj_count);
    return dest_ptr;
}

Uint r2r_memcpy(Uint dest, Uint src, Uint obj_count, Uint obj_size) {
    Uint bytes = obj_count * obj_size;
    assert(((dest-src) >= bytes) || (src-dest) >= bytes);
    Uchar *d, *s;
    while(bytes--)
        *d++ = *s++;
    return (Uint)d;
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
