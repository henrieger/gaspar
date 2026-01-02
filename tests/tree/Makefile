CC = gcc
CFLAGS = -g -Wall -I../../src -march=native
LDLIBS =
OBJECTS = *.o

all: run clean

tree: tree.o ../../src/tree/tree.o ../../src/sequence-alignment/sequence-alignment.o ../../src/utils/math.o
tree.o: tree.c

iterator: iterator.o ../../src/tree/iterator.o ../../src/tree/tree.o ../../src/sequence-alignment/sequence-alignment.o ../../src/utils/math.o
iterator.o: iterator.c

random: random.o ../../src/tree/random.o ../../src/tree/iterator.o ../../src/tree/tree.o ../../src/sequence-alignment/sequence-alignment.o ../../src/utils/math.o
random.o: random.c

run: tree iterator random
	valgrind ./tree
	valgrind ./iterator
	valgrind ./random

clean:
	rm -f tree iterator random $(OBJECTS)
