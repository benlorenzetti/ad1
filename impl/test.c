#include <stdio.h>
#include "ad1strlib.h"
#include "ad1stdio.h"

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
  s1 = fromCstr(s1, "hello world!\n");
  print_str(stdout, str_2ndhalf(s1));
  s1 = string_cat(s1, str_2ndhalf(s1));
  print_str(stdout, str_2ndhalf(s1));
  str_dealloc(&s1);

  FILE* tfile = fopen("lorem-ipsum.txt", "r");
  string s2 = str_init();
  s2 = str_realloc(s2, -1000);
  slice intermediate = str_spacea(s2);
  printf("space available = %u, %u len %u\n", -intermediate.zero, -intermediate.nth, intermediate.zero-intermediate.nth);
  intermediate = slc_read(intermediate, tfile, -1);
  s2 = str_splice(s2, intermediate);
  printf("1st half = %u, %u\n", -str_1sthalf(s2).zero, -str_1sthalf(s2).nth);
  printf("2nd half = %u, %u\n", -str_2ndhalf(s2).zero, -str_2ndhalf(s2).nth);
  print_str(stdout, str_2ndhalf(s2));
  fclose(tfile);
  str_dealloc(&s2);
}
