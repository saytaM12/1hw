CC := clang
OUT := main
CFLAGS := -g -Wall -std=c11 -lm -pedantic
RFLAGS := -std=c17 -lm -DNDEBUG -O3
PRIMESSRC := ./src/eratosthenes.c ./src/error.c ./src/primes.c
PRIMESOBJS := $(patsubst ./src/%.c, ./obj/%.o, $(PRIMESSRC))
STEGSRC := ./src/eratosthenes.c ./src/error.c ./src/ppm.c ./src/steg-decode.c
STEGOBJS := $(patsubst ./src/%.c, ./obj/%.o, $(STEGSRC))
TARGET := main

eratosthenes.c: eratosthenes.h bitset.h
error.c: error.h
ppm.c: ppm.h error.c
primes.c: bitset.h eratosthenes.c
steg-decode: bitset.h ppm.c eratosthenes.c

all: primes primes-i steg-decode

run: primes primes-i
	./primes ulimit -s 20000
	./primes-i ulimit -s 20000

.PHONY: primes
primes:
	mkdir -p obj
	make inprimes CFLAGS="$(CFLAGS) -DPRIMES_MAIN" TARGET="primes"

.PHONY: primes-i
primes-i:
	mkdir -p obj
	make inprimes CFLAGS="$(CFLAGS) -DUSE_INLINE -DPRIMES_MAIN" TARGET="primes-i"

.PHONY: steg-decode
steg-decode:
	mkdir -p obj
	make insteg-decode CFLAGS="$(CFLAGS) -DSTEG_MAIN" TARGET="steg-decode"

.PHONY: inprimes
inprimes: $(PRIMESOBJS)
	$(CC) $(CFLAGS) $^ -o $(TARGET)

.PHONY: insteg-decode
insteg-decode: $(STEGOBJS)
	$(CC) $(CFLAGS) $^ -o $(TARGET)

obj/%.o: src/%.c
	$(CC) $(CFLAGS) $^ -o $@

.PHONY: clean
clean:
	rm ./obj/*.o
