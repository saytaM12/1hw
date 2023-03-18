// error.c
// Řešení IJC-DU1, příklad b), 20.3.2023
// Autor: Matyáš Oujezdský, FIT
// Přeloženo: clang version 10.0.0-4ubuntu1
#include "error.h"

void warning(const char *fmt, ...)
{
    va_list ap;
    va_start (ap, fmt);
    fputs("Warning: ", stderr);
    vfprintf (stderr, fmt, ap);
    va_end(ap);
}
void error_exit(const char *fmt, ...)
{
    va_list ap;
    va_start (ap, fmt);
    fputs("Error: ", stderr);
    vfprintf (stderr, fmt, ap);
    va_end(ap);
    exit(1);
}
