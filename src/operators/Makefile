CC = gcc
CFLAGS = -Wall -I..
LDLIBS = 
OBJECTS = nni.o

all: $(OBJECTS)
nni.o: nni.c nni.h

optimize: CFLAGS += -O3
optimize: all

debug: CFLAGS += -g -DDEBUG
debug: all

profile: CFLAGS += -pg
profile: all

clean:
	rm -f $(OBJECTS)
