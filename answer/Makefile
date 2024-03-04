CC = gcc
CFLAGS = -Wall -I..
LDLIBS = 
OBJECTS = *.o

all: answer.o
answer.o: answer.c answer.h

debug: CFLAGS += -g -DDEBUG
debug: all

clean:
	rm -f $(OBJECTS)
