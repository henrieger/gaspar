CC = gcc
CFLAGS = -Wall -I..
LDLIBS = 
OBJECTS = tree.o tree-traversal.o

all: $(OBJECTS)
tree.o: tree.c tree.h
tree-traversal.o: tree.o tree-traversal.c tree-traversal.h

debug: CFLAGS += -g -DDEBUG
debug: all

clean:
	rm -f $(OBJECTS)
