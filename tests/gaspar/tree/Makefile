INCLUDE_DIR = ../../../include
SRC_DIR = ../../../src/gaspar
CC = gcc
CFLAGS = -g -Wall -I${INCLUDE_DIR} -march=native
LDLIBS =
OBJECTS = *.o

all: run clean

tree: tree.o ${SRC_DIR}/tree/tree.o ${SRC_DIR}/sequence-alignment/sequence-alignment.o ${SRC_DIR}/utils/math.o
tree.o: tree.c

iterator: iterator.o ${SRC_DIR}/tree/iterator.o ${SRC_DIR}/tree/tree.o ${SRC_DIR}/sequence-alignment/sequence-alignment.o ${SRC_DIR}/utils/math.o
iterator.o: iterator.c

random: random.o ${SRC_DIR}/tree/random.o ${SRC_DIR}/tree/iterator.o ${SRC_DIR}/tree/tree.o ${SRC_DIR}/sequence-alignment/sequence-alignment.o ${SRC_DIR}/utils/math.o
random.o: random.c

run: tree iterator random
	valgrind ./tree
	valgrind ./iterator
	valgrind ./random

clean:
	rm -f tree iterator random $(OBJECTS)
