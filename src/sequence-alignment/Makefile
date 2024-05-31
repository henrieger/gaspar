CC = gcc
CFLAGS = -Wall -I.. -mavx
LDLIBS = 
OBJECTS = *.o

all: sequence-alignment.o
sequence-alignment.o: sequence-alignment.c sequence-alignment.h

optimize: CFLAGS += -O3
optimize: all

debug: CFLAGS += -g -DDEBUG
debug: all

profile: CFLAGS += -pg -O0
profile: all

clean:
	rm -f $(OBJECTS)
