INCLUDE_DIR = ../../../include
SRC_DIR = ../../../src/gaspar
CC = gcc
CFLAGS = -g -Wall -I${INCLUDE_DIR} -march=native
LDLIBS = -lm
OBJECTS = *.o

all: run clean

answer: answer.o ${SRC_DIR}/answer/answer.o ${SRC_DIR}/tree/tree.o ${SRC_DIR}/sequence-alignment/sequence-alignment.o ${SRC_DIR}/utils/math.o
answer.o: answer.c

run: answer
	valgrind ./answer

clean:
	rm -f answer $(OBJECTS)
