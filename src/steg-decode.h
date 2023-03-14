// steg-decode.h
// Řešení IJC-DU1, příklad b), 20.3.2023
// Autor: Matyáš Oujezdský, FIT
// Přeloženo: clang version 10.0.0-4ubuntu1
#ifndef STEG_DECODE_INCLUDED
#define STEG_DECODE_INCLUDED

#include <stdio.h>
#include "error.h"
#include "bitset.h"
#include "ppm.h"
#include "eratosthenes.h"

void read_msg(struct ppm* img, bitset_t b);

#endif
