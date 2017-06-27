#ifndef STDOI_H
#define STDOI_H

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

typedef unsigned char Wchar;
typedef char cstr;

#define STDOI_CONVERSION_BUFFER_SIZE 1024

FILE* oi_fiopen(const cstr *, const cstr *);
int oi_fclose(FILE *);
int oi_printf(const cstr *, ...);
int oi_fprintf(FILE *, const cstr *, ...);
int oi_putchar(int);


#endif
