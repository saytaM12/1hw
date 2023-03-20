// steg-decode.c
// Řešení IJC-DU1, příklad b), 20.3.2023
// Autor: Matyáš Oujezdský, FIT
// Přeloženo: clang version 10.0.0-4ubuntu1
#include <stdio.h>
#include <stdlib.h>
#include "error.h"
#include "bitset.h"
#include "ppm.h"
#include "eratosthenes.h"

unsigned char* read_msg(struct ppm* img, bitset_t b, bitset_index_t start)
{
    unsigned char nextchar = 0;
    int strsize = 8;
    unsigned char *tmpstr = calloc(strsize, sizeof(unsigned char));
    int charcount = 0;
    int bitcount = 0;
    for (bitset_index_t i = start; i < bitset_size(b); ++i)
    {
        if (!bitset_getbit(b, i))
        {
            nextchar |= (img->data[i] & 1) << bitcount;
            bitcount++;

            if (bitcount == 8)
            {
                tmpstr[charcount] = nextchar;
                if (nextchar == 0)
                    return tmpstr;
                bitcount = 0;
                nextchar = 0;

                if (++charcount > strsize)
                {
                    strsize *= 2;
                    tmpstr = realloc(tmpstr, strsize);
                }
                tmpstr[charcount] = 0;
            }
        }
    }
    warning("read_msg: Nebyl nalezen konec řetězce ve zprávě\n");
    return NULL;
}

/*
 * The utf8_check() function scans the '\0'-terminated string starting
 * at s. It returns a pointer to the first byte of the first malformed
 * or overlong UTF-8 sequence found, or NULL if the string contains
 * only correct UTF-8. It also spots UTF-8 sequences that could cause
 * trouble if converted to UTF-16, namely surrogate characters
 * (U+D800..U+DFFF) and non-Unicode positions (U+FFFE..U+FFFF). This
 * routine is very likely to find a malformed sequence if the input
 * uses any other encoding than UTF-8. It therefore can be used as a
 * very effective heuristic for distinguishing between UTF-8 and other
 * encodings.
 *
 * I wrote this code mainly as a specification of functionality; there
 * are no doubt performance optimizations possible for certain CPUs.
 *
 * Markus Kuhn <http://www.cl.cam.ac.uk/~mgk25/> -- 2005-03-30
 * License: http://www.cl.cam.ac.uk/~mgk25/short-license.html
 */
unsigned char *utf8_check(unsigned char *s)
{
  while (*s) {
    if (*s < 0x80)
      /* 0xxxxxxx */
      s++;
    else if ((s[0] & 0xe0) == 0xc0) {
      /* 110XXXXx 10xxxxxx */
      if ((s[1] & 0xc0) != 0x80 ||
	  (s[0] & 0xfe) == 0xc0)                        /* overlong? */
	return s;
      else
	s += 2;
    } else if ((s[0] & 0xf0) == 0xe0) {
      /* 1110XXXX 10Xxxxxx 10xxxxxx */
      if ((s[1] & 0xc0) != 0x80 ||
	  (s[2] & 0xc0) != 0x80 ||
	  (s[0] == 0xe0 && (s[1] & 0xe0) == 0x80) ||    /* overlong? */
	  (s[0] == 0xed && (s[1] & 0xe0) == 0xa0) ||    /* surrogate? */
	  (s[0] == 0xef && s[1] == 0xbf &&
	   (s[2] & 0xfe) == 0xbe))                      /* U+FFFE or U+FFFF? */
	return s;
      else
	s += 3;
    } else if ((s[0] & 0xf8) == 0xf0) {
      /* 11110XXX 10XXxxxx 10xxxxxx 10xxxxxx */
      if ((s[1] & 0xc0) != 0x80 ||
	  (s[2] & 0xc0) != 0x80 ||
	  (s[3] & 0xc0) != 0x80 ||
	  (s[0] == 0xf0 && (s[1] & 0xf0) == 0x80) ||    /* overlong? */
	  (s[0] == 0xf4 && s[1] > 0x8f) || s[0] > 0xf4) /* > U+10FFFF? */
	return s;
      else
	s += 4;
    } else
      return s;
  }

  return NULL;
}

int main(int argc, char** argv)
{
    if (argc != 2) {
        error_exit("main: Nesprávný počet vstupních argumentů");
    }

    struct ppm* img = ppm_read(argv[1]);
    bitset_alloc(b, 3 * img->xsize * img->ysize);
    
    eratosthenes(b);
    
    unsigned char *msg = read_msg(img, b, 101);
    if (utf8_check(msg))
        error_exit("Zpráva není UTF-8");
    
    printf("%s", msg);
    
    bitset_free(b);
    ppm_free(img);

    return 0;
}
