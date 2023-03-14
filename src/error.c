// error.c
// Řešení IJC-DU1, příklad b), 20.3.2023
// Autor: Matyáš Oujezdský, FIT
// Přeloženo: clang version 10.0.0-4ubuntu1
#include "error.h"

void warning(const char *fmt, ...)
{
    va_list args;
    va_start (args, fmt);
    fputs("Warning: ", stderr);
    vfprintf (stderr, fmt, args);
    va_end (args);
}
void error_exit(const char *fmt, ...)
{
    va_list args;
    va_start (args, fmt);
    fputs("Error: ", stderr);
    vfprintf (stderr, fmt, args);
    va_end (args);
    exit(1);
}
