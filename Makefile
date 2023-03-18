CC := clang
OUT := main
CFLAGS := -g -Wall -std=c11 -lm -pedantic
RFLAGS := -std=c17 -lm -DNDEBUG -O3
SRC := $(wildcard ./src/*.c)
PRIMESOBJS := $(patsubst ./src/%.c, ./obj/%.o, $(SRC))
TARGET := main

-include tmp

all: primes primes-i steg-decode

run: all
	./primes ulimit -s 20000
	./primes-i ulimit -s 20000

.PHONY: primes
primes:
	mkdir -p obj
	clang $(CFLAGS) -MM $(SRC) > tmp
	make inprimes TARGET="primes"

.PHONY: primes-i
primes-i:
	mkdir -p obj
	clang $(CFLAGS) -MM $(SRC) > tmp
	make inprimes CFLAGS="$(CFLAGS) -DUSE_INLINE" TARGET="primes-i"

.PHONY: steg-decode
steg-decode:
	mkdir -p obj
	clang $(CFLAGS) -MM $(SRC) > tmp
	make insteg-decode TARGET="steg-decode"

.PHONY: insteg-decode
insteg-decode: obj/steg-decode.o obj/primes.o obj/ppm.o obj/eratosthenes.o
	$(CC) $(CFLAGS) $^ -o $<

.PHONY: inprimes
inprimes: $(PRIMESOBJS)
	$(CC) $(CFLAGS) $^ -o $(TARGET)

obj/%.o: src/%.c
	$(CC) $(CFLAGS) $^ -o $@

.PHONY: clean
clean:
	rm ./obj/*.o
