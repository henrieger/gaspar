INCLUDE_DIR = ../../../include
SRC_DIR = ../../../src/gaspar
CC = gcc
CFLAGS = -g -Wall -I${INCLUDE_DIR} -mno-avx
LDLIBS = -lm
OBJECTS = *.o

all: run clean

bootstrap: bootstrap.o ${SRC_DIR}/support/bootstrap.o ${SRC_DIR}/search/genetic-algorithm.o	${SRC_DIR}/answer/answer.o ${SRC_DIR}/tree/tree.o ${SRC_DIR}/tree/iterator.o ${SRC_DIR}/tree/random.o	${SRC_DIR}/sequence-alignment/sequence-alignment.o ${SRC_DIR}/eval/parsimony.o ${SRC_DIR}/operators/spr.o ${SRC_DIR}/utils/math.o ${SRC_DIR}/base/config.o
bootstrap.o: bootstrap.c

run: bootstrap
	valgrind -s --track-origins=yes ./bootstrap

clean:
	rm -f bootstrap $(OBJECTS)
