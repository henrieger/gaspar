CC = gcc
CFLAGS = -Wall -I..
LDLIBS = 
OBJECTS = *.o

all: sequence-alignment.o
sequence-alignment.o: sequence-alignment.c sequence-alignment.h

debug: CFLAGS += -g -DDEBUG
debug: all

clean:
	rm -f $(OBJECTS)
