// bitset.h
// Řešení IJC-DU1, příklad a), 20.3.2023
// Autor: Matyáš Oujezdský, FIT
// Přeloženo: clang version 10.0.0-4ubuntu1
#ifndef BITSET_INCLUDED
#define BITSET_INCLUDED

#include <assert.h>
#include <limits.h>
#include <stdlib.h>
#include "error.h"

typedef unsigned long* bitset_t;

typedef unsigned long bitset_index_t;

#define UL_BITS (CHAR_BIT * sizeof(bitset_index_t))

#define __bitset_setbit__(arr_param, index_param, value_param)\
    do{\
        bitset_t arr = (arr_param);\
        bitset_index_t index = (index_param);\
        if (index > arr[0])\
        {\
            error_exit("bitset_setbit: Index %lu outside range 0..%lu", index, arr[0]);\
        }\
        if (value_param)\
            arr[index / UL_BITS + 1] |= (1L << index % UL_BITS);\
        else\
            arr[index / UL_BITS + 1] &= ~(1L << index % UL_BITS);\
    }while(0)

static inline void bitset_free(bitset_t arr_param)
{
    free(arr_param);
}

static inline bitset_index_t bitset_size(bitset_t arr_param)
{
    return arr_param[0];
}

static inline void bitset_setbit(bitset_t arr_param, bitset_index_t index_param, _Bool value_param)
{
      __bitset_setbit__(arr_param, index_param, value_param);
}

static inline _Bool bitset_getbit(bitset_t arr, bitset_index_t index)
{
    if (index > arr[0])
        error_exit("bitset_getbit: Index %lu outside range 0..%lu", index, arr[0]);
    return (arr[index/UL_BITS + 1] & (1L << index % UL_BITS));
}

#define bitset_create(arr_param, size_param)\
    unsigned long arr_param[(size_param - 1) / UL_BITS + 2 * sizeof(bitset_index_t)] = {size_param};\
    static_assert(size_param > 0, "Wrong size")
                      
#define bitset_alloc(arr_param, size_param)\
    bitset_t arr_param;\
    do{\
        bitset_index_t size = (size_param);\
        arr_param = calloc((size - 1) / UL_BITS + 2, sizeof(bitset_index_t));\
        if (arr_param)\
            arr_param[0] = size;\
        else\
            error_exit("bitset_alloc: Chyba alokace paměti");\
    }while(0)

#define bitset_free(arr_param)\
                    free(arr_param)

#define bitset_size(arr_param)\
                   (arr_param)[0]

#define bitset_setbit(arr_param, index_param, value_param)\
      __bitset_setbit__(arr_param, index_param, value_param)

#define bitset_getbit(arr_param, index_param)\
        bitset_getbit(arr_param, index_param)

#endif
