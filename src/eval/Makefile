CC = gcc
CFLAGS = -Wall -I..
LDLIBS = 
OBJECTS = *.o

all: parsimony.o
parsimony.o: parsimony.c parsimony.h

optimize: CFLAGS += -O3 -mavx2
optimize: all

debug: CFLAGS += -g -DDEBUG
debug: all

profile: CFLAGS += -pg
profile: all

clean:
	rm -f $(OBJECTS)
