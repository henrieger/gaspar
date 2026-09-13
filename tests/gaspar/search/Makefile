INCLUDE_DIR = ../../../include
SRC_DIR = ../../../src/gaspar
CC = gcc
CFLAGS = -g -Wall -I${INCLUDE_DIR} -march=native
LDLIBS = -lm
OBJECTS = *.o

all: run clean

correct-tree.o: correct-tree.c correct-tree.h

genetic-algorithm: genetic-algorithm.o correct-tree.o ${SRC_DIR}/search/genetic-algorithm.o ${SRC_DIR}/answer/answer.o ${SRC_DIR}/tree/tree.o ${SRC_DIR}/tree/iterator.o ${SRC_DIR}/tree/random.o ${SRC_DIR}/sequence-alignment/sequence-alignment.o ${SRC_DIR}/eval/parsimony.o ${SRC_DIR}/operators/nni.o ${SRC_DIR}/operators/spr.o ${SRC_DIR}/operators/subtree-swap.o ${SRC_DIR}/operators/hybrid.o ${SRC_DIR}/utils/math.o
genetic-algorithm.o: genetic-algorithm.c

hill-climbing: hill-climbing.o correct-tree.o ${SRC_DIR}/search/hill-climbing.o ${SRC_DIR}/answer/answer.o ${SRC_DIR}/tree/tree.o ${SRC_DIR}/tree/iterator.o ${SRC_DIR}/tree/random.o ${SRC_DIR}/sequence-alignment/sequence-alignment.o ${SRC_DIR}/eval/parsimony.o ${SRC_DIR}/operators/nni.o ${SRC_DIR}/operators/spr.o ${SRC_DIR}/operators/subtree-swap.o ${SRC_DIR}/utils/math.o
hill-climbing.o: hill-climbing.c

branch-and-bound: branch-and-bound.o correct-tree.o ${SRC_DIR}/search/branch-and-bound.o ${SRC_DIR}/answer/answer.o ${SRC_DIR}/tree/tree.o ${SRC_DIR}/tree/iterator.o ${SRC_DIR}/sequence-alignment/sequence-alignment.o ${SRC_DIR}/eval/parsimony.o ${SRC_DIR}/utils/math.o
branch-and-bound.o: branch-and-bound.c

run: genetic-algorithm hill-climbing branch-and-bound
	valgrind ./genetic-algorithm 
	valgrind ./hill-climbing
	valgrind ./branch-and-bound

clean:
	rm -f genetic-algorithm hill-climbing branch-and-bound $(OBJECTS)
