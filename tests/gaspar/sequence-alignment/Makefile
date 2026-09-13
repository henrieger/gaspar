INCLUDE_DIR = ../../../include
SRC_DIR = ../../../src/gaspar
CC = gcc
CFLAGS = -g -Wall -I${INCLUDE_DIR} -march=native
LDLIBS =
OBJECTS = *.o

all: run clean

sequence-alignment: sequence-alignment.o ${SRC_DIR}/sequence-alignment/sequence-alignment.o ${SRC_DIR}/utils/math.o
sequence-alignment.o: sequence-alignment.c

run: sequence-alignment
	valgrind ./sequence-alignment

clean:
	rm -f sequence-alignment $(OBJECTS)
