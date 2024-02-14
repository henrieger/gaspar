CC = gcc
CFLAGS = -Wall -I..
LDLIBS = 
OBJECTS = *.o

all: parsimony.o
parsimony.o: parsimony.c parsimony.h

debug: CFLAGS += -g -DDEBUG
debug: all

clean:
	rm -f $(OBJECTS)
