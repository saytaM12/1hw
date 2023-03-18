// ppm.c
// Řešení IJC-DU1, příklad b), 20.3.2023
// Autor: Matyáš Oujezdský, FIT
// Přeloženo: clang version 10.0.0-4ubuntu1
#include "ppm.h"

struct ppm* ppm_read(const char* filename)
{
    FILE* f = fopen(filename, "rb");
    char format[3];
    unsigned size[2];

    fscanf(f, "%s", format);
    if (strcmp(format, "P6") != 0)
        {
            warning("Wrong format");
            return NULL;
        }

    fscanf(f, "%d %d 255%*c", &size[0], &size[1]);

    struct ppm* img = malloc(2 * sizeof(unsigned) + 3 * size[0] * size[1]);
    img->xsize = size[0];
    img->ysize = size[1];

    if (size[0] * size[1] != fread(img->data, 3, img->xsize * img->ysize, f))
        error_exit("Invalid data");

    fclose(f);

    return img;
}

void ppm_free(struct ppm* p)
{
    free(p);;
}
