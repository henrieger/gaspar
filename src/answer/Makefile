CC = gcc
CFLAGS = -Wall -I..
LDLIBS = 
OBJECTS = *.o

all: answer.o
answer.o: answer.c answer.h

optimize: CFLAGS += -O3
optimize: all

debug: CFLAGS += -g -DDEBUG
debug: all

profile: CFLAGS += -pg
profile: all

clean:
	rm -f $(OBJECTS)
