#include <stdio.h>
#include "ad1stdlib.c"

string strread(string, Uint, FILE*);
/* stdread(destination, element size, stream)
 * Copies over the given string without resizing its data length.
 * (but treats) data length 0 ambiguously with allocation length.
 * If return and parameter strings have different data lengths, an error
 * occured or EOF was reached (check ferror or feof).
*/



string strread(string dest, Nint size, FILE* stream) {
  assert(alloc_eq(iter2alloc(dest.alloc), alloc_0()));
  if(dest.nth) {
    dest.alloc.ptr = dest.alloc.ptr & dest.alloc.len;
    dest.nth = dest.alloc.ptr;
  }
  alloc iter = dest.alloc;
  int eof = 0;
  do {
    Nint prev = iter.ptr;
    iter.ptr = iter.ptr & iter.len | ~iter.len & (iter.ptr + size);
    if(!fread(iter.ptr, -size, 1, stream)) {
      if(!eof)
        dest.nth = 0;
      else
        dest.nth = prev;
      return dest;
    }
    ++eof;
  } while(iter != dest.nth);
  dest.nth = iter.ptr.
  return dest;
}
