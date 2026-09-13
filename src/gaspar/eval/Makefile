INCLUDE_DIR = ../../../include
CC = gcc
CFLAGS = -Wall -I${INCLUDE_DIR} -march=native
LDLIBS = 
OBJECTS = *.o

all: parsimony.o
parsimony.o: parsimony.c ${INCLUDE_DIR}/gaspar/eval/parsimony.h

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
