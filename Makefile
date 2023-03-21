CC := clang
CFLAGS := -g -Wall -std=c11 -lm -pedantic -Wextra -O3 -fsanitize=address

all: directory primes primes-i steg-decode

run: directory primes primes-i
	ulimit -s 30000 ; ./primes|factor
	ulimit -s 30000 ; ./primes-i

directory:
	mkdir -p obj

primes: obj/eratosthenes.o obj/error.o obj/primes.o
	$(CC) $(CFLAGS) $^ -o $@

primes-i: obj/eratosthenes-i.o obj/error-i.o obj/primes-i.o
	$(CC) $(CFLAGS) $^ -o $@

steg-decode: obj/eratosthenes.o obj/error.o obj/ppm.o obj/steg-decode.o
	$(CC) $(CFLAGS) $^ -o $@


obj/eratosthenes.o: src/eratosthenes.c src/eratosthenes.h src/bitset.h src/error.h
obj/error.o: src/error.c src/error.h
obj/primes.o: src/primes.c src/bitset.h src/error.h src/eratosthenes.h
obj/eratosthenes-i.o: src/eratosthenes.c src/eratosthenes.h src/bitset.h src/error.h
obj/error-i.o: src/error.c src/error.h
obj/primes-i.o: src/primes.c src/bitset.h src/error.h src/eratosthenes.h
obj/ppm.o: src/ppm.c src/ppm.h src/error.h
obj/steg-decode.o: src/steg-decode.c src/error.h src/bitset.h src/ppm.h src/eratosthenes.h

obj/%.o: src/%.c
	$(CC) $(CFLAGS) $< -c -o $@

obj/%-i.o: src/%.c
	$(CC) $(CFLAGS) $< -DUSE_INLINE -c -o $@


.PHONY: clean
clean:
	-rm -r ./obj/ primes primes-i steg-decode
