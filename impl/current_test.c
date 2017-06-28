#include <stdio.h>
#include "stdoi.h"
#include "string.h"
#include "pivlib.h"
#include "array.h"

int char_compare(Nint a, Nint b) {
//    Wchar* aptr = (Wchar*)a;
//    Wchar* bptr = (Wchar*)b;
//    printf("cmp '%c' to '%c'\n", *aptr, *bptr);
    return ((Wchar*)a)[0] - ((Wchar*)b)[0];
}

int main() {
    STRING_MAIN_ASSERT();
    ustr string1 = c2ustr("Hello World!");
    ustr string2 = c2ustr("Hello");
    oi_fprintf(stdout, "ustr string1 = %S\n", string1);
    oi_fprintf(stdout, "ustr string2 = %S\n\n", string2);

    Wchar* str1 = ustr_get_str(&string1);
    Wchar* str2 = ustr_get_str(&string2);
    oi_fprintf(stdout, "Wchar* str1 = %s\n", str1);
    oi_fprintf(stdout, "Wchar* str2 = %s\n", str2);
    printf("&str1 = %lu\n&str2 = %lu\n\n", (Nint)str1, (Nint)str2);


    rvec vec1 = ustr_get_rvec(&string1);
    rvec vec2 = ustr_get_rvec(&string2);
    printf("vec1 = (%lu, %lu]\n", vec1.zero, vec1.nth);
    printf("vec2 = (%lu, %lu]\n", vec2.zero, vec2.nth);

    printf("rvec_cmp(vec1, vec2, 1, char_compare) = ");
    printf("%d\n\n", rvec_cmp(vec1, vec2, 1, char_compare));

    ustr_free(string1);
    ustr_free(string2);

}
