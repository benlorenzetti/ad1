#include "ad1stdlib.h"
#include <string.h>
#include <stdio.h>

typedef struct str {
  Nint nth;
  Uint zero;
} str;

typedef struct alloc {
  Uint ptr;
  Nint len;
} alloc;

struct string {
  Nint nth;
  alloc alloc;
};

typedef union string_union {
  Nint nth;
  str str;
  struct string string;
} string;

string string_init() {
  string new_string;
  new_string.string.nth = 0;
  new_string.string.alloc.ptr = 0;
  new_string.string.alloc.len = 0;
  return new_string;
}

void string_clear(string* a) {
  Nint alloc_len = a->string.alloc.len;
  Nint alloc_end = alloc_len & a->string.alloc.ptr;
}

string fromCstr(string* a, const char* c) {
  Nint len = -((Nint) strlen(c));
  // Allocate new memory if required
  if(len < a->string.alloc.len) {

  }
  return *a;
}
