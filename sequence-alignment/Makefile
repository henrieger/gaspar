CC = gcc
CFLAGS = -g -Wall -I.. -O3
LDLIBS = 
OBJECTS = *.o

all: sequence-alignment.o
sequence-alignment.o: sequence-alignment.c sequence-alignment.h

debug: CFLAGS += -g -DDEBUG
debug: all

profile: CFLAGS += -pg
profile: all

clean:
	rm -f $(OBJECTS)
