CC = gcc
CFLAGS = -Wall
OBJECTS = *.o
EXECUTABLE = test-trees

test-trees: test-trees.c tree.o

tree.o: tree.c tree.h

debug: CFLAGS += -g -DDEBUG
debug: test-trees

clean:
	rm -f $(OBJECTS)

purge: clean
	rm -f $(EXECUTABLE)
