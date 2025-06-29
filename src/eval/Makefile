CC = gcc
CFLAGS = -Wall -I.. -march=native
LDLIBS = 
OBJECTS = *.o

all: parsimony.o
parsimony.o: parsimony.c parsimony.h

optimize: CFLAGS += -O3
optimize: all

debug: CFLAGS += -g -DDEBUG -fsanitize=address
debug: all

profile: CFLAGS += -pg -O0
profile: all

clean:
	rm -f $(OBJECTS)
