#include "pivlib.h"
#include <stdio.h>
#include "stdoi.h"
#include "string.h"
#include <stdint.h>

int main() {
    Nint testptr = 0;
    printf("Max unsigned pointer value = %lu\n", UINTPTR_MAX);
    printf("              uintptr_test = %lu\n", testptr -1);

    Nint x = -129;
    printf("x = %ld\n", x);
    printf("floor = %d\n", log2floor(x));
    printf("ceil = %d\n", log2ceil(x));
    printf("power2(ceil) = %ld\n", power2N(log2ceil(x)));

    Wchar array1[5] = {'e', 'd', 'c', 'b', 0};
    Wchar array2[5];
    Nint ar1 = (Nint)array1 + 5;
    Nint ar2 = (Nint)array2 + 5;
    memcpy(ar2, ar1, -5);
    printf("array2 = %s\n", array2);


    Wchar str1[5] = {0, 'd', 'c', 'b', 'a'};
    Wchar* str2 = &str1[5];
    oi_fprintf(stdout, "string test = %s, int test = %d\n", str2, 27); 

    // Test c2ustr() constructor and sfree() destructor
    ustr str3 = c2ustr("123456789");
    oi_fprintf(stdout, "c2ustr(\"xyz\") = %s\n", str3.str);
    sfree(str3);
}
