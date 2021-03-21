#include "ad1stdlib.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>

typedef struct string {
  Nint nth;
  iter iter;
} string;

string str_init();
void str_dealloc(string*);
string str_empty(string);
Nint str_len(string);
string str_realloc(string, Nint);
/* str_realloc(original string, n) consumes the original string and returns
 * a new string with the same original data and at least n additional bytes
 * available
 * (XOR returns an error 1 on allocation failure (linear unimplemented)).
 */
iter str_alloc(string, Nint);
/* str_alloc(orig_string, append_len) never consumes the input string.
 * Returns a new allocation if orig string is of insufficient capacity
 * to hold the append length
 * XOR returns an empty alloc_0 if orig string has sufficient capacity..
 * (XOR returns an error 1 on allocation failure (linear unimplemented)).
 */
string string_cat(string, slice);
string fromCstr(string, const char*);
slice str_1sthalf(string);
slice str_2ndhalf(string);
void print_str(FILE*, slice);
slice str_spacea(string);
/* str_spacea(string) returns an empty slice of memory equivalent to the
 * first half of empty space in the string available but not filled.
 */
slice str_move(slice, string*);
/* str_copy(dest, src) returns a slice of size <= dest filled with data
 * copied from the left side of the src string.
 * Modifies the source string by removing the copied data from the left.
 */
string str_splice(string, slice);

string str_init() {
  string new_string;
  new_string.nth = 0;
  new_string.iter = alloc2iter(alloc_0());
  return new_string;
}

string str_empty(string str) {
  str.nth = 0;
  return str;
}

void str_dealloc(string* a) {
  if(iter_eq(a->iter, iter_0()))
    geofree(iter2alloc(a->iter));
  a->nth = 0;
  a->iter = alloc2iter(alloc_0());
}

string fromCstr(string str, const char* cstr) {
  Nint len = -((Nint) strlen(cstr));
  str = str_realloc(str_empty(str), len);
  str.nth = (str.iter.ptr & str.iter.len) - str.iter.len;
  str.nth = r2l_memcpy(str.nth, (Nint)cstr, len, sizeof(char));
  return str;
}

iter str_alloc(string str, Nint append_len) {
  printf("  str_alloc((%u, %u, %u], %u)\n", -str.nth, -str.iter.ptr, -str.iter.len, -append_len);
  Nint len = 0;
  if(str.nth)
    len = (str.nth < str.iter.ptr) ? str.nth - str.iter.ptr : str.iter.len - (str.iter.ptr - str.nth);
  printf("len = %u\n", -len);
  if(str.iter.len > len + append_len || !iter_eq(str.iter, iter_0())) {
    // Allocate New String
    printf("allocating new iterator...\n");
    Uchar power = log2ceil(len + append_len);
    return alloc2iter(geomalloc(power));
  }
  else
    return iter_0();
}

string str_realloc(string str, Nint append_len) {
  printf("str_realloc((%u, %u, %u], %u)\n", -str.nth, -str.iter.ptr, -str.iter.len, -append_len);
  string new;
  new.iter = str_alloc(str, append_len);
  printf("new.iter = %u, %u\n", -new.iter.ptr, -new.iter.len);
  if(0 == iter_eq(new.iter, iter_0()))
    return str;
  // Copy to new string
  if(str.nth) {
    new.nth = new.iter.ptr - new.iter.len;
    new.nth = l2l_memcpy(new.nth, str_1sthalf(str));
    new.nth = l2l_memcpy(new.nth, str_2ndhalf(str));
  }
  geofree(iter2alloc(str.iter));
  return new;
}

string string_cat(string dest, slice append) {
  string new;
  new.iter = str_alloc(dest, slc_len(append));
  if(iter_eq(new.iter, iter_0()) != 0) {
    // Copy old dest string to new string
    new.nth = new.iter.ptr - new.iter.len;
    new.nth = l2l_memcpy(new.nth, str_1sthalf(dest));
    new.nth = l2l_memcpy(new.nth, str_2ndhalf(dest));
    new.nth = l2l_memcpy(new.nth, append);
    geofree(iter2alloc(dest.iter));
    return new;
  }
  while (slc_len(append)) {
    slice tofill = str_spacea(dest);
    tofill = slc_copy(tofill, append);
    dest = str_splice(dest, tofill);
    append.zero = append.zero + slc_len(tofill);
  }
  return dest;
}

slice str_1sthalf(string str) {
  slice slc = {0, 0};
  // A first half exists if nth <= zero in N (but its size may be zero)
  if(str.nth >= str.iter.ptr) {
    slc.zero = str.iter.ptr;
    slc.nth = str.iter.ptr & str.iter.len;
  }
  return slc;
}

slice str_2ndhalf(string str) {
  slice slc = {0, 0};
  if(!str.nth)
    return slc;
  // Second halves exist, either with string pointers as stored (zero, nth] or
  // from the allocation left end (alloc lend, nth] if their is a first half
  Nint alloc_end = str.iter.ptr & str.iter.len;
  if(str.iter.ptr > str.nth)
    slc.zero = str.iter.ptr;
  else
    slc.zero = alloc_end - str.iter.len;
  slc.nth = str.nth;
  return slc;
}

void print_str(FILE* stream, slice s) {
  assert(s.nth);
  assert(s.nth <= s.zero);
  if(s.nth != s.zero);
  do {
    char c = ((char*)(--s.zero))[0];
    fputc(c, stream);
  } while(s.nth != s.zero);
}

slice str_spacea(string str) {
  assert(iter_eq(str.iter, iter_0()));
  slice space;
  if(str.nth == str.iter.ptr) { // existing data; already full
    space.nth = 0;
    space.zero = 0;
    return space;
  }
  alloc rend = iter2alloc(str.iter);
  if(!str.nth) {// empty of existing data
    space.nth = rend.ptr;
    space.zero = rend.ptr - rend.len;
    return space;
  }
  else if(str.iter.ptr > str.nth) {
    space.nth = rend.ptr;
    space.zero = str.nth;
  }
  else {
    space.nth = str.iter.ptr;
    space.zero = rend.ptr - rend.len;
  }
  return space;
}

slice str_move(slice dest, string* src) {
  assert(dest.zero != dest.nth);
  Nint iter = dest.zero;
  int halves = 0;
  slice half;
  do {
    if(halves == 0) {
      half = str_1sthalf(*src);
      halves++;
    }
    if(halves == 1) {
      half = str_2ndhalf(*src);
      halves++;
    }
    if(halves > 1)
      break;
    if(dest.nth - iter > half.nth - half.zero )
      iter = iter - (half.nth - half.zero);
    iter = r2r_memcpy(iter, half);
  } while(iter != dest.nth);
  src->iter.ptr = half.nth;
  dest.nth = iter;
  return dest;
}

string str_splice(string left, slice right) {
  assert(left.nth == right.zero);
  left.nth = right.nth;
  return left;
}

Nint str_len(string str) {
  return str.iter.len & (str.nth - str.iter.ptr);
}
