#include "ad1stdlib.h"
#include <string.h>
#include <stdio.h>

typedef struct str {
  Nint nth;
  Uint zero;
} str;

typedef struct lvec {
  Uint end;
  Nint alloc_len;
} lvec;

struct string {
  Nint nth;
  lvec zero;
};

typedef union string_union {
  Nint nth;
  str str;
  struct string string;
} string;

string string_init() {
  string new_string;
  new_string.string.nth = 0;
  new_string.string.zero.end = 0;
  new_string.string.zero.alloc_len = -1;
  return new_string;
}

string fromCstr(string* a, const char* c) {
  Uint size = (Uint) strlen(c);
  // Allocate new memory if required

  return *a;
}
