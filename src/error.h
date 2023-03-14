// error.h
// Řešení IJC-DU1, příklad b), 20.3.2023
// Autor: Matyáš Oujezdský, FIT
// Přeloženo: clang version 10.0.0-4ubuntu1
#ifndef ERROR_INNCLUDED
#define ERROR_INNCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void warning(const char *fmt, ...);
void error_exit(const char *fmt, ...);

#endif
