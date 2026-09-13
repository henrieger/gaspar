INCLUDE_DIR = ../../../include
CC = gcc
CFLAGS = -Wall -I${INCLUDE_DIR}
LDLIBS = 
OBJECTS = tree.o random.o iterator.o

all: $(OBJECTS)
tree.o: tree.c ${INCLUDE_DIR}/gaspar/tree/tree.h
random.o: random.c ${INCLUDE_DIR}/gaspar/tree/random.h
iterator.o: iterator.c ${INCLUDE_DIR}/gaspar/tree/iterator.h

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
