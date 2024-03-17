CC = gcc
CFLAGS = -g -Wall -I.. -O3
LDLIBS = 
OBJECTS = *.o

all: branch-and-bound.o
branch-and-bound.o: branch-and-bound.c branch-and-bound.h

debug: CFLAGS += -g -DDEBUG
debug: all

profile: CFLAGS += -pg
profile: all

clean:
	rm -f $(OBJECTS)
