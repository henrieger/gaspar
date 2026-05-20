CC = gcc
CFLAGS = -Wall -I..
LDLIBS =
OBJECTS = nni.o spr.o hybrid.o subtree-swap.o

all: $(OBJECTS)
nni.o: nni.c nni.h
spr.o: spr.c spr.h
hybrid.o: hybrid.c hybrid.h
subtree-swap.o: subtree-swap.c subtree-swap.h

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
