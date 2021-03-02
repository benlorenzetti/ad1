#include <stdio.h>
#include "ad1stdlib.c"

slice strread(slice, Uint, FILE*);
/* stdread(destination, element size, stream)
 * Returns a filled slice. If return and parameter slices have different size,
 * an error occured or EOF was reached (check ferror or feof).
*/

slice strread(slice dest, Nint size, FILE* stream) {
  assert(dest.nth < dest.zero);
  do {
    dest.zero += size;
    if(!fread(dest, -size, 1, stream)) {
      dest.zero -= size;
      break;
    }
  } while(dest.zero != dest.nth);
}
