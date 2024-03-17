CC = gcc
CFLAGS = -g -Wall -I.. -O3
LDLIBS = 
OBJECTS = tree.o tree-traversal.o

all: $(OBJECTS)
tree.o: tree.c tree.h
tree-traversal.o: tree-traversal.c tree-traversal.h

debug: CFLAGS += -g -DDEBUG
debug: all

profile: CFLAGS += -pg
profile: all

clean:
	rm -f $(OBJECTS)
