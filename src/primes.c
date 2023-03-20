// primes.c
// Řešení IJC-DU1, příklad a), 20.3.2023
// Autor: Matyáš Oujezdský, FIT
// Přeloženo: clang version 10.0.0-4ubuntu1
#include <stdio.h>
#include <time.h>
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

int main()
{
    int start = clock();
    bitset_create(b, 23000000);
    eratosthenes(b);
    lastPrimes(b, 10);
    fprintf(stderr, "Time=%.3g\n", (double)(clock()-start)/CLOCKS_PER_SEC);
    return 0;
}
