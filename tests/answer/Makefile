CC = gcc
CFLAGS = -g -Wall -I../../src -march=native
LDLIBS =
OBJECTS = *.o

all: run clean

answer: answer.o ../../src/answer/answer.o ../../src/tree/tree.o ../../src/sequence-alignment/sequence-alignment.o ../../src/sequence-alignment/mask-operations.o ../../src/utils/math.o
answer.o: answer.c

run: answer
	valgrind ./answer

clean:
	rm -f answer $(OBJECTS)
