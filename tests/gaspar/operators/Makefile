INCLUDE_DIR = ../../../include
SRC_DIR = ../../../src/gaspar
CC = gcc
CFLAGS = -g  -Wall -I${INCLUDE_DIR} -march=native
LDLIBS =
OBJECTS = *.o

all: run clean

nni: nni.o ${SRC_DIR}/operators/nni.o ${SRC_DIR}/tree/tree.o ${SRC_DIR}/tree/iterator.o ${SRC_DIR}/tree/random.o ${SRC_DIR}/sequence-alignment/sequence-alignment.o ${SRC_DIR}/utils/math.o
nni.o: nni.c

spr: spr.o ${SRC_DIR}/operators/spr.o ${SRC_DIR}/tree/tree.o ${SRC_DIR}/tree/iterator.o ${SRC_DIR}/tree/random.o ${SRC_DIR}/sequence-alignment/sequence-alignment.o ${SRC_DIR}/utils/math.o
spr.o: spr.c

hybrid: hybrid.o ${SRC_DIR}/operators/hybrid.o ${SRC_DIR}/operators/nni.o ${SRC_DIR}/operators/spr.o ${SRC_DIR}/tree/tree.o ${SRC_DIR}/tree/iterator.o ${SRC_DIR}/tree/random.o ${SRC_DIR}/sequence-alignment/sequence-alignment.o ${SRC_DIR}/utils/math.o
hybrid.o: hybrid.c

subtree-swap: subtree-swap.o ${SRC_DIR}/operators/subtree-swap.o ${SRC_DIR}/tree/tree.o ${SRC_DIR}/tree/iterator.o ${SRC_DIR}/tree/random.o ${SRC_DIR}/sequence-alignment/sequence-alignment.o ${SRC_DIR}/utils/math.o
subtree-swap.o: subtree-swap.c

run: nni spr hybrid subtree-swap
	valgrind ./nni
	valgrind ./spr
	valgrind ./hybrid
	valgrind ./subtree-swap

clean:
	rm -f nni spr hybrid subtree-swap $(OBJECTS)
