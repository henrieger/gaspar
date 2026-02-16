CC = gcc
CFLAGS = -g  -Wall -I../../src -march=native
LDLIBS =
OBJECTS = *.o

all: run clean

nni: nni.o ../../src/operators/nni.o ../../src/tree/tree.o ../../src/tree/iterator.o ../../src/tree/random.o ../../src/sequence-alignment/sequence-alignment.o ../../src/utils/math.o
nni.o: nni.c

spr: spr.o ../../src/operators/spr.o ../../src/tree/tree.o ../../src/tree/iterator.o ../../src/tree/random.o ../../src/sequence-alignment/sequence-alignment.o ../../src/utils/math.o
spr.o: spr.c

hybrid: hybrid.o ../../src/operators/hybrid.o ../../src/operators/nni.o ../../src/operators/spr.o ../../src/tree/tree.o ../../src/tree/iterator.o ../../src/tree/random.o ../../src/sequence-alignment/sequence-alignment.o ../../src/utils/math.o
hybrid.o: hybrid.c

run: nni spr hybrid
	valgrind ./nni
	valgrind ./spr
	valgrind ./hybrid

clean:
	rm -f nni spr $(OBJECTS)
