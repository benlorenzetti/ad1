#ifndef AD1STDIO_H
#define AD1STDIO_H

#include <stdio.h>
#include "ad1stdlib.h"

slice slc_read(slice, FILE*, Nint);
/* stdread(dest, stream, word_len)
 *
*/

slice slc_read(slice dest, FILE* stream, Nint word_len) {
  assert(slc_len(dest));
  assert((-slc_len(dest)) % (-word_len) == 0);
  Nint ptr = dest.zero;
  size_t one = 1;
  printf("fread: ");
  do {
    ptr += word_len;
    one = fread((void*)ptr, -word_len, 1, stream);
    printf("%c", *((char*)ptr));
    if(one != 1) {
      if(feof(stream))
        dest.nth = ++ptr;
      else {
        printf("slc_read file error\n");
        break;
      }
    }
  } while(ptr != dest.nth);
  printf("break\n");
  return dest;
}

#endif
