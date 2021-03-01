#include <stdio.h>
#include "ad1strlib.h"

int main () {
  string s1 = string_init();
  Nint memory = geomalloc(5);
  Nint memory2 = geomalloc(5);
  Nint memory3 = geomalloc(5);
  print_malloc_metadata();
  geofree(memory, -32);
  geofree(memory2, -32);
  geofree(memory3, -32);
  print_malloc_metadata();
  Uint big = 31;
  printf("log2floor()=%u\n", log2floor(big));
  printf("log2ceil()= %u\n", log2ceil(-big));
}
