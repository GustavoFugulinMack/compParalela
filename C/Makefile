CC=gcc
CFLAGS=-O3 -Wall
OMPFLAGS=-fopenmp
LDFLAGS=-lm

all: nbody nbody_parallel convert

nbody: nbody.c
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

nbody_parallel: nbody_parallel.c
	$(CC) $(CFLAGS) $(OMPFLAGS) $< -o $@ $(LDFLAGS)

convert: convert.c
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

clean:
	rm -f nbody nbody_parallel convert

