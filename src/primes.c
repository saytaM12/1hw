// primes.c
// Řešení IJC-DU1, příklad a), 20.3.2023
// Autor: Matyáš Oujezdský, FIT
// Přeloženo: clang version 10.0.0-4ubuntu1
#include <stdio.h>
#include "bitset.h"
#include "eratosthenes.h"

void lastPrimes (bitset_t b, int count)
{
    int prime_count = 0;
    int i;
    for (i = bitset_size(b); prime_count < count; --i)
        if (!bitset_getbit(b, i))
            ++prime_count;
    for (; i < bitset_size(b); ++i)
        if (!bitset_getbit(b, i))
            printf("%d\n", i);
}

#ifdef PRIMES_MAIN

int main()
{
    bitset_create(b, 23000000);
    eratosthenes(b);
    lastPrimes(b, 10);
    return 0;;
}

#endif // PRIMES_MAIN
