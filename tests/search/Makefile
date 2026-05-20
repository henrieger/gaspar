CC = gcc
CFLAGS = -g -Wall -I../../src -march=native
LDLIBS = -lm
OBJECTS = *.o

all: run clean

genetic-algorithm: genetic-algorithm.o ../../src/search/genetic-algorithm.o ../../src/answer/answer.o ../../src/tree/tree.o ../../src/tree/iterator.o ../../src/tree/random.o ../../src/sequence-alignment/sequence-alignment.o ../../src/eval/parsimony.o ../../src/operators/nni.o ../../src/operators/spr.o ../../src/operators/hybrid.o ../../src/utils/math.o
genetic-algorithm.o: genetic-algorithm.c

hill-climbing: hill-climbing.o ../../src/search/hill-climbing.o ../../src/answer/answer.o ../../src/tree/tree.o ../../src/tree/iterator.o ../../src/tree/random.o ../../src/sequence-alignment/sequence-alignment.o ../../src/eval/parsimony.o ../../src/operators/nni.o ../../src/operators/spr.o ../../src/utils/math.o
hill-climbing.o: hill-climbing.c

branch-and-bound: branch-and-bound.o ../../src/search/branch-and-bound.o ../../src/answer/answer.o ../../src/tree/tree.o ../../src/tree/iterator.o ../../src/sequence-alignment/sequence-alignment.o ../../src/eval/parsimony.o ../../src/utils/math.o
branch-and-bound.o: branch-and-bound.c

run: genetic-algorithm hill-climbing branch-and-bound
	valgrind ./genetic-algorithm 
	valgrind ./hill-climbing
	valgrind ./branch-and-bound

clean:
	rm -f genetic-algorithm hill-climbing branch-and-bound $(OBJECTS)
