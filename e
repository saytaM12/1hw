CC := clang
OUT := main
CFLAGS := -g -Wall -std=c11 -lm -pedantic
RFLAGS := -std=c17 -lm -DNDEBUG -O3

-include tmp

all: primes primes-i steg-decode

run: all


primes:
	mkdir obj
	clang $(CFLAGS) -MM $(SRC) | sed -r 's/.*:(.*)/\1/' > tmp
	make inprimes

inprimes: $(OBJS)
	$(CC) $(CFLAGS) obj/primes.o obj/error.o obj/eratosthenes.o -o $<

obj/%.o: src/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

primes-i: obj/primes-i.o obj/error-i.o obj/eratosthenes-i.o
	$(CC) $(CFLAGS) obj/primes-i.o obj/error-i.o obj/eratosthenes-i.o -o $<

steg-decode: obj/steg-decode.o obj/primes.o obj/ppm.o obj/eratosthenes.o

obj/steg-decode.o: src/steg-decode.c src/error.h src/bitset.h src/ppm.h src/eratosthenes.h
	$(CC) $(CFLAGS) src/steg-decode.c -o $<

obj/ppm.o: src/ppm.c src/ppm.h src/error.h
	$(CC) $(CFLAGS) src/ppm.c -o $<


.PHONY: clean
clean:
	rm ./obj/*.o
