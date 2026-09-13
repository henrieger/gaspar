INCLUDE_DIR = ../../../include
CC = gcc
CFLAGS = -Wall -I${INCLUDE_DIR} -march=native
LDLIBS = 
OBJECTS = *.o

all: sequence-alignment.o
sequence-alignment.o: sequence-alignment.c ${INCLUDE_DIR}/gaspar/sequence-alignment/sequence-alignment.h

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
