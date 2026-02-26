CC = gcc
CFLAGS = -g -Wall -I../../src -march=native
LDLIBS =
OBJECTS = *.o

all: run clean

parsimony: parsimony.o ../../src/eval/parsimony.o ../../src/tree/tree.o ../../src/sequence-alignment/sequence-alignment.o ../../src/utils/math.o
parsimony.o: parsimony.c

run: parsimony
	valgrind ./parsimony

clean:
	rm -f parsimony $(OBJECTS)
