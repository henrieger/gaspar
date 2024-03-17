CC = gcc
CFLAGS = -g -Wall -I.. -O3
LDLIBS = 
OBJECTS = *.o

all: answer.o
answer.o: answer.c answer.h

debug: CFLAGS += -g -DDEBUG
debug: all

profile: CFLAGS += -pg
profile: all

clean:
	rm -f $(OBJECTS)
