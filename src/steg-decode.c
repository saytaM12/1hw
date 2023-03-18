// steg-decode.c
// Řešení IJC-DU1, příklad b), 20.3.2023
// Autor: Matyáš Oujezdský, FIT
// Přeloženo: clang version 10.0.0-4ubuntu1
#include "steg-decode.h"

void read_msg(struct ppm* img, bitset_t b)
{
    unsigned char tmpchar = 0;
    int countchar = 0;
    for (int i = 101; i < bitset_size(b); ++i)
    {
        if (!bitset_getbit(b, i))
        {
            tmpchar |= (img->data[i] & 1) << countchar;
            countchar++;
        }
        if (countchar == 8)
        {
            putchar(tmpchar);
            if (tmpchar == '\0')
                return;
            countchar = 0;
            tmpchar = 0;
        }
    }
            
}

#ifdef steg_main

int main()
{
    struct ppm* img = ppm_read("img.ppm");
    bitset_alloc(b, 3 * img->xsize * img->ysize);
    eratosthenes(b);
    read_msg(img, b);
}

#endif // steg_main
