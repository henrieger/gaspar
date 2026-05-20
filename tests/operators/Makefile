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

subtree-swap: subtree-swap.o ../../src/operators/subtree-swap.o ../../src/tree/tree.o ../../src/tree/iterator.o ../../src/tree/random.o ../../src/sequence-alignment/sequence-alignment.o ../../src/utils/math.o
subtree-swap.o: subtree-swap.c

run: nni spr hybrid subtree-swap
	valgrind ./nni
	valgrind ./spr
	valgrind ./hybrid
	valgrind ./subtree-swap

clean:
	rm -f nni spr hybrid subtree-swap $(OBJECTS)
