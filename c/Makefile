CC = gcc
CFLAGS = -Wall
OBJECTS = *.o
EXECUTABLE = test-trees test-sequence-alignment test-parsimony

all: $(EXECUTABLE)

test-trees: test-trees.c tree.o
test-sequence-alignment: test-sequence-alignment.c sequence-alignment.o
test-parsimony: test-parsimony.c sequence-alignment.o tree.o parsimony.o

tree.o: tree.c tree.h sequence-alignment.o
sequence-alignment.o: sequence-alignment.c sequence-alignment.h
parsimony.o: parsimony.c parsimony.h tree.o

debug: CFLAGS += -g -DDEBUG
debug: all

clean:
	rm -f $(OBJECTS)

purge: clean
	rm -f $(EXECUTABLE)
