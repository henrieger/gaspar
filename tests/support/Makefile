CC = gcc
CFLAGS = -g -Wall -I../../src -march=native
LDLIBS = -lm
OBJECTS = *.o

all: run clean

bootstrap: bootstrap.o ../../src/support/bootstrap.o ../../src/search/genetic-algorithm.o	../../src/answer/answer.o ../../src/tree/tree.o ../../src/tree/iterator.o ../../src/tree/random.o	../../src/sequence-alignment/sequence-alignment.o ../../src/eval/parsimony.o ../../src/operators/spr.o ../../src/utils/math.o ../../src/config.o
bootstrap.o: bootstrap.c

run: bootstrap
	valgrind -s --track-origins=yes ./bootstrap

clean:
	rm -f bootstrap $(OBJECTS)
