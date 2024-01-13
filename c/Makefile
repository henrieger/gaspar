CC = gcc
CFLAGS = -Wall
OBJECTS = *.o
EXECUTABLE = test-trees

test-trees: test-trees.c tree.o
test-sequence-alignment: test-sequence-alignment.c sequence-alignment.o

tree.o: tree.c tree.h
sequence-alignment.o: sequence-alignment.c sequence-alignment.h

debug: CFLAGS += -g -DDEBUG
debug: test-trees

clean:
	rm -f $(OBJECTS)

purge: clean
	rm -f $(EXECUTABLE)
