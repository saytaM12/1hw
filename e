CC := clang
OUT := main
CFLAGS := -g -Wall -std=c11 -lm -pedantic
RFLAGS := -std=c17 -lm -DNDEBUG -O3


all: primes primes-i steg-decode

run: all


primes: obj/primes.o obj/error.o obj/eratosthenes.o
	$(CC) $(CFLAGS) obj/primes.o obj/error.o obj/eratosthenes.o -o $<

obj/primes.o: $(shell clang -MM ./src/primes.c | sed -r "s/.*:(.*)/\1/")
	$(info $^)
	$(CC) $(CFLAGS) src/primes.c -o $<

obj/error.o: src/error.c src/error.h
	$(CC) $(CFLAGS) src/error.c -o $<

obj/eratosthenes.o: src/eratosthenes.c src/eratosthenes.h src/bitset.h src/error.h
	$(CC) $(CFLAGS) src/eratosthenes.c -o $<


primes-i: obj/primes-i.o obj/error-i.o obj/eratosthenes-i.o
	$(CC) $(CFLAGS) obj/primes-i.o obj/error-i.o obj/eratosthenes-i.o -o $<

obj/primes-i.o: src/primes.c src/ppm.h src/bitset.h src/error.h src/eratosthenes.h
	$(CC) $(CFLAGS) -DUSE-INLINE src/primes.c -o $<

obj/error-i.o: src/error.c src/error.h
	$(CC) $(CFLAGS) -DUSE-INLINE src/error.c -o $<

obj/eratosthenes-i.o: src/eratosthenes.c src/eratosthenes.h src/bitset.h src/error.h
	$(CC) $(CFLAGS) -DUSE-INLINE src/eratosthenes.c -o $<


steg-decode: obj/steg-decode.o obj/primes.o obj/ppm.o obj/eratosthenes.o

obj/steg-decode.o: src/steg-decode.c src/error.h src/bitset.h src/ppm.h src/eratosthenes.h
	$(CC) $(CFLAGS) src/steg-decode.c -o $<

obj/ppm.o: src/ppm.c src/ppm.h src/error.h
	$(CC) $(CFLAGS) src/ppm.c -o $<


.PHONY: clean
clean:
	rm ./obj/*.o
