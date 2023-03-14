CC:=cc
TARGET:=main
CFLAGS:=-g -Wall -std=c17 -fsanitize=address
RFLAGS:=-std=c17 -DNDEBUG -O3

SRC:=$(wildcard src/*.c)
DOBJ:=$(patsubst src/%.c, obj/debug/%.o, $(SRC))
ROBJ:=$(patsubst src/%.c, obj/release/%.o, $(SRC))

-include dep.d

obj/debug/steg-decode.o: src/steg-decode.c src/steg-decode.h src/error.h \
obj/debug/  src/bitset.h src/ppm.h src/eratosthenes.h
obj/debug/error.o: src/error.c src/error.h
obj/debug/primes.o: src/primes.c src/primes.h src/error.h src/bitset.h \
obj/debug/  src/eratosthenes.h
obj/debug/eratosthenes.o: src/eratosthenes.c src/eratosthenes.h src/bitset.h \
obj/debug/  src/error.h
obj/debug/ppm.o: src/ppm.c src/ppm.h src/error.h


.DEFAULT_GOAL:=debug

.PHONY: debug
.PHONY: release
.PHONY: install
.PHONY: clean
.PHONY: rel
.PHONY: deb


debug:
	mkdir -p obj/debug
	clang $(CFLAGS) -MM $(SRC) | sed -r 's/^.*$$/obj\/debug\/\0/' > dep.d
	make deb

release:
	mkdir -p obj/release
	clang $(CFLAGS) -MM $(SRC) | sed -r 's/^.*$$/obj\/release\/\0/' > dep.d
	make rel

deb: $(DOBJ)
	$(CC) $(CFLAGS) $^ -o $(TARGET)

rel: $(ROBJ)
	$(CC) $(RFLAGS) $^ -o $(TARGET)

obj/debug/%.o:
	$(CC) $(CFLAGS) -c -o $@ $<

obj/release/%.o: src/%.c
	$(CC) $(RFLAGS) -c -o $@ $<

install:
	sudo cp -i $(TARGET) /bin/target

clean:
	rm obj/debug/*.o || true
	rm obj/release/*.o || true
	rm $(TARGET) || true
