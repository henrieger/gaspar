INCLUDE_DIR = ../../../include
SRC_DIR = ../../../src/gaspar
CC = gcc
CFLAGS = -g -Wall -I${INCLUDE_DIR} -mno-avx
LDLIBS =
OBJECTS = *.o

all: run clean

parsimony: parsimony.o ${SRC_DIR}/eval/parsimony.o ${SRC_DIR}/tree/tree.o ${SRC_DIR}/sequence-alignment/sequence-alignment.o ${SRC_DIR}/utils/math.o
parsimony.o: parsimony.c

run: parsimony
	valgrind ./parsimony

clean:
	rm -f parsimony $(OBJECTS)
