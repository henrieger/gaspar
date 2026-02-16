CC = gcc
CFLAGS = -g -Wall -I../../src -march=native
LDLIBS = -lm
OBJECTS = *.o

all: run clean

genetic-algorithm: genetic-algorithm.o ../../src/search/genetic-algorithm.o \
	../../src/answer/answer.o ../../src/tree/tree.o ../../src/tree/iterator.o ../../src/tree/random.o \
	../../src/sequence-alignment/sequence-alignment.o ../../src/sequence-alignment/mask-operations.o \
	../../src/eval/parsimony.o ../../src/operators/nni.o ../../src/operators/spr.o ../../src/operators/hybrid.o \
	../../src/utils/math.o
genetic-algorithm.o: genetic-algorithm.c

run: genetic-algorithm
	valgrind ./genetic-algorithm

clean:
	rm -f genetic-algorithm $(OBJECTS)
