INCLUDE_DIR = ../../../include
CC = gcc
CFLAGS = -Wall -I${INCLUDE_DIR}
LDLIBS =
OBJECTS = nni.o spr.o hybrid.o subtree-swap.o

all: $(OBJECTS)
nni.o: nni.c ${INCLUDE_DIR}/gaspar/operators/nni.h
spr.o: spr.c ${INCLUDE_DIR}/gaspar/operators/spr.h
hybrid.o: hybrid.c ${INCLUDE_DIR}/gaspar/operators/hybrid.h
subtree-swap.o: subtree-swap.c ${INCLUDE_DIR}/gaspar/operators/subtree-swap.h

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
