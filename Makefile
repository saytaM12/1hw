CC := clang
CFLAGS := -g -Wall -std=c11 -lm -pedantic

all: directory primes primes-i steg-decode

run: primes primes-i
	./primes ulimit -s 20000
	./primes-i ulimit -s 20000

directory:
	mkdir -p obj

primes: obj/eratosthenes.o obj/error.o obj/primes.o
	$(CC) $(CFLAGS) $^ -o $@

primes-i: obj/eratosthenes.o obj/error.o obj/primes-i.o
	$(CC) $(CFLAGS) $^ -o $@

steg-decode: obj/eratosthenes.o obj/error.o obj/ppm.o obj/steg-decode.o
	$(CC) $(CFLAGS) $^ -o $@


obj/eratosthenes.o: src/eratosthenes.c src/eratosthenes.h src/bitset.h src/error.h
	$(CC) $(CFLAGS) src/eratosthenes.c -c -o obj/eratosthenes.o

obj/error.o: src/error.c src/error.h
	$(CC) $(CFLAGS) src/error.c -c -o obj/error.o

obj/primes.o: src/primes.c src/bitset.h src/error.h src/eratosthenes.h
	$(CC) $(CFLAGS) src/primes.c -DPRIMES_MAIN -c -o obj/primes.o

obj/primes-i.o: src/primes.c src/bitset.h src/error.h src/eratosthenes.h
	$(CC) $(CFLAGS) src/primes.c -DPRIMES_MAIN -DUSE_INLINE -c -o obj/primes-i.o

obj/ppm.o: src/ppm.c src/ppm.h src/error.h
	$(CC) $(CFLAGS) src/ppm.c -c -o obj/ppm.o

obj/steg-decode.o: src/steg-decode.c src/error.h src/bitset.h src/ppm.h src/eratosthenes.h
	$(CC) $(CFLAGS) src/steg-decode.c -DSTEG_MAIN -c -o obj/steg-decode.o


#obj/%.o: src/%.c
#	$(CC) $(CFLAGS) $^ -c -o $@

.PHONY: clean
clean:
	rm -r ./obj/ primes primes-i steg-decode

#eratosthenes.c: src/eratosthenes.h src/bitset.h
#bitset.h: src/error.c
#error.c: src/error.h
#ppm.c: src/ppm.h src/error.c
#primes.c: src/bitset.h src/eratosthenes.c
#steg-decode.c: src/bitset.h src/ppm.c src/eratosthenes.c
