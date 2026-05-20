CC = gcc
CFLAGS = -Wall -I..
LDLIBS =
OBJECTS = *.o

all: genetic-algorithm.o hill-climbing.o branch-and-bound.o
branch-and-bound.o: branch-and-bound.c branch-and-bound.h
hill-climbing.o: hill-climbing.c hill-climbing.h
genetic-algorithm.o: genetic-algorithm.c genetic-algorithm.h

optimize: CFLAGS += -O3
optimize: all

debug: CFLAGS += -g -DDEBUG
debug: all

sanitize: CFLAGS += -g -fsanitize=address
sanitize: all

profile: CFLAGS += -pg -O0
profile: all

clean:
	rm -f $(OBJECTS)
