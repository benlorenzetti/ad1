#include "ad1stdlib.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>

typedef struct string {
  Nint nth;
  alloc alloc;
} string;

string str_init();
void str_zero(string*);
string str_clear(string);
string str_realloc(string, Nint);
/* str_realloc(original string, n) preserves the original string and returns
 * either a new string with at least n additional bytes available or the
 * original string.
 */
string string_cat(string*, slice);
string fromCstr(string*, const char*);
slice str_1sthalf(string);
slice str_2ndhalf(string);
void print_str(FILE*, slice);


 slice spacea(string);
 string spaceapp(string, slice);

string str_init() {
  string new_string;
  new_string.nth = 0;
  new_string.alloc.ptr = 0;
  new_string.alloc.len = 0;
  return new_string;
}

string str_clear(string str) {
  str.nth = 0;
  return str;
}

void str_zero(string* a) {
  if(a->alloc.ptr)
    geofree(a->alloc);
    a->nth = 0;
    a->alloc.ptr = 0;
    a->alloc.len = 0;
}

string fromCstr(string* str, const char* cstr) {
  Nint len = -((Nint) strlen(cstr));
  *str = str_clear(*str);
  *str = str_realloc(*str, len);
  assert(!str->nth); // preserved from clear through reserve
  str->nth = (str->alloc.ptr & str->alloc.len) - str->alloc.len;
  str->nth = r2l_memcpy(str->nth, (Nint)cstr, len, sizeof(char));
  return *str;
}

string str_realloc(string str, Nint append_len) {
  string r = str;
  Nint len = 0;
  if(r.nth)
    len = (r.nth < r.alloc.ptr) ? r.nth - r.alloc.ptr : r.alloc.len - (r.alloc.ptr - r.nth);
  if(r.alloc.len > len + append_len || !r.alloc.len && (len+append_len)) {
    // Allocate New String
    Uchar power = log2ceil(len + append_len);
    r.alloc = geomalloc(power);
    // Copy to new string
    if(r.nth) {
      r.nth = r.alloc.ptr - r.alloc.len;
      r.nth = l2l_memcpy(r.nth, str_1sthalf(str));
      r.nth = l2l_memcpy(r.nth, str_2ndhalf(str));
    }
  }
  return r;
}

string string_cat(string* a, slice append) {
  string r = str_realloc(*a, append.nth - append.zero);
  int deallocation_deferred = (a->alloc.ptr - r.alloc.ptr);
  if(!r.nth && append.nth != append.zero)
    r.nth = (r.alloc.len & r.alloc.ptr) - r.alloc.len;
  r.nth = l2l_memcpy(r.nth, append);
  if (deallocation_deferred)
    geofree(a->alloc);
  *a = r;
  return r;
}

slice str_1sthalf(string str) {
  slice slc = {0, 0};
  // A first half exists if nth <= zero in N (but its size may be zero)
  if(str.nth >= str.alloc.ptr) {
    slc.zero = str.alloc.ptr;
    slc.nth = str.alloc.ptr & str.alloc.len;
  }
  return slc;
}

slice str_2ndhalf(string str) {
  slice slc = {0, 0};
  if(!str.nth)
    return slc;
  // Second halves exist, either with string pointers as stored (zero, nth] or
  // from the allocation left end (alloc lend, nth] if their is a first half
  Nint alloc_end = str.alloc.ptr & str.alloc.len;
  if(str.alloc.ptr > str.nth)
    slc.zero = str.alloc.ptr;
  else
    slc.zero = alloc_end - str.alloc.len;
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

slice spacea(string str) {
  slice slc;
  assert(str.alloc.ptr);
  Nint alloc_end = str.alloc.ptr & str.alloc.len;
  if(!str.nth) // empty
    slc.nth = alloc_end, slc.zero = alloc_end - str.alloc.len;
  if(str.nth == str.alloc.ptr) // existing data; already full
    slc.nth = 0, slc.zero = alloc_end;
  else if(str.nth > str.alloc.ptr) // existing data wraps around
    slc.nth = str.alloc.ptr, slc.zero = str.nth;
  else { // existing data is contiguous with empty space to the left
    if (str.nth != alloc_end) // there is also empty space to the right
      slc.nth = alloc_end, slc.zero = str.nth;
    else // allocate from space at the leftmost portion of allocation
      slc.nth = alloc_end - str.alloc.len, slc.zero = str.alloc.ptr;
  }
  return slc;
}

string spaceapp(string str, slice slc) {
  Nint alloc_left_end = str.alloc.ptr & str.alloc.len - str.alloc.len;
  assert(slc.zero == str.nth || slc.zero == alloc_left_end);
  str.nth = slc.nth;
  return str;
}
