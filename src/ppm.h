// ppm.h
// Řešení IJC-DU1, příklad b), 20.3.2023
// Autor: Matyáš Oujezdský, FIT
// Přeloženo: clang version 10.0.0-4ubuntu1
#ifndef PPM_INCLUDED
#define PPM_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "error.h"

struct ppm {
    unsigned xsize;
    unsigned ysize;
    char data[];
};

struct ppm* ppm_read(const char* filename);

void ppm_free(struct ppm* p);

#endif
