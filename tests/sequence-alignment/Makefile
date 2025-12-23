CC = gcc
CFLAGS = -g -Wall -I../../src -march=native
LDLIBS =
OBJECTS = *.o

all: run clean

sequence-alignment: sequence-alignment.o ../../src/sequence-alignment/sequence-alignment.o ../../src/utils/math.o
sequence-alignment.o: sequence-alignment.c

mask-operations: mask-operations.o ../../src/sequence-alignment/sequence-alignment.o ../../src/sequence-alignment/mask-operations.o ../../src/utils/math.o
mask-operations.o: mask-operations.c

run: sequence-alignment mask-operations
	valgrind ./sequence-alignment
	valgrind ./mask-operations

clean:
	rm -f sequence-alignment mask-operations $(OBJECTS)
