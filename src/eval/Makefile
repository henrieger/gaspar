CC = gcc
CFLAGS = -Wall -I.. -march=native
LDLIBS = 
OBJECTS = *.o

all: parsimony.o
parsimony.o: parsimony.c parsimony.h

optimize: CFLAGS += -O3
optimize: all

debug: CFLAGS += -g -DDEBUG
debug: all

sanitize: CFLAGS += -fsanitize=address
sanitize: debug

profile: CFLAGS += -pg -O0
profile: all

clean:
	rm -f $(OBJECTS)
