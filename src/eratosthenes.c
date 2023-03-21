// eartosthenes.c
// Řešení IJC-DU1, příklad a), 20.3.2023
// Autor: Matyáš Oujezdský, FIT
// Přeloženo: clang version 10.0.0-4ubuntu1
#include <math.h>
#include "eratosthenes.h"

void eratosthenes(bitset_t b)
{
    bitset_setbit(b, 0, 1);
    bitset_setbit(b, 1, 1);
    bitset_index_t limit = sqrt(bitset_size(b));
    for (bitset_index_t i = 2; i <= limit; ++i)
        if (!bitset_getbit(b, i))
            for (bitset_index_t j = i * i; j <= bitset_size(b); j += i)
                bitset_setbit(b, j, 1);
}
