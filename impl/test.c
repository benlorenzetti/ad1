#include <stdio.h>
#include "ad1strlib.h"

int main () {
  alloc memory = geomalloc(5);
  alloc memory2 = geomalloc(5);
  alloc memory3 = geomalloc(5);
  print_malloc_metadata();
  geofree(memory);
  geofree(memory2);
  geofree(memory3);
  print_malloc_metadata();
  Uint big = 31;
  printf("log2floor()=%u\n", log2floor(big));
  printf("log2ceil()= %u\n", log2ceil(-big));
  string s1 = str_init();
  s1 = fromCstr(&s1, "hello world!\n");
  print_str(stdout, str_2ndhalf(s1));
  s1 = string_cat(&s1, str_2ndhalf(s1));
  print_str(stdout, str_2ndhalf(s1));
  str_zero(&s1);
}
