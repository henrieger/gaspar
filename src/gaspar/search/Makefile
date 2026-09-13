INCLUDE_DIR = ../../../include
CC = gcc
CFLAGS = -Wall -I${INCLUDE_DIR}
LDLIBS =
OBJECTS = *.o

all: genetic-algorithm.o hill-climbing.o branch-and-bound.o
branch-and-bound.o: branch-and-bound.c ${INCLUDE_DIR}/gaspar/search/branch-and-bound.h
hill-climbing.o: hill-climbing.c ${INCLUDE_DIR}/gaspar/search/hill-climbing.h
genetic-algorithm.o: genetic-algorithm.c ${INCLUDE_DIR}/gaspar/search/genetic-algorithm.h

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
