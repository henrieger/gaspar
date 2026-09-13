INCLUDE_DIR = ../../../include
SRC_DIR = ../../../src/gaspar
CC = gcc
CFLAGS = -g -Wall -I${INCLUDE_DIR} -march=native
LDLIBS = -lm
OBJECTS = *.o

all: run clean

config: config.o ${SRC_DIR}/base/config.o ${SRC_DIR}/eval/parsimony.o ${SRC_DIR}/operators/spr.o ${SRC_DIR}/sequence-alignment/sequence-alignment.o ${SRC_DIR}/utils/math.o ${SRC_DIR}/tree/tree.o ${SRC_DIR}/tree/iterator.o ${SRC_DIR}/tree/random.o ${SRC_DIR}/search/genetic-algorithm.o ${SRC_DIR}/answer/answer.o
config.o: config.c

functions: functions.o ${SRC_DIR}/base/functions.o ${SRC_DIR}/base/config.o ${SRC_DIR}/eval/parsimony.o ${SRC_DIR}/operators/spr.o ${SRC_DIR}/sequence-alignment/sequence-alignment.o ${SRC_DIR}/utils/math.o ${SRC_DIR}/tree/tree.o ${SRC_DIR}/tree/iterator.o ${SRC_DIR}/tree/random.o ${SRC_DIR}/search/genetic-algorithm.o ${SRC_DIR}/answer/answer.o
functions.o: functions.c

run: config functions
	valgrind ./config
	valgrind ./functions

clean:
	rm -f answer $(OBJECTS)
