CC = gcc
CFLAGS = -g -Wall -I../../src -march=native
LDLIBS =
OBJECTS = *.o

all: run clean

sequence-alignment: sequence-alignment.o ../../src/sequence-alignment/sequence-alignment.o ../../src/utils/math.o
sequence-alignment.o: sequence-alignment.c

run: sequence-alignment
	valgrind ./sequence-alignment

clean:
	rm -f sequence-alignment $(OBJECTS)
