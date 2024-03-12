CC = gcc
CFLAGS = -Wall -I..
OBJECTS = *.o
EXECUTABLES = test-trees test-sequence-alignment test-parsimony

all: $(EXECUTABLES)

test-trees: test-trees.c ../tree/tree.o ../tree/tree-traversal.o ../sequence-alignment/sequence-alignment.o
test-sequence-alignment: test-sequence-alignment.c ../sequence-alignment/sequence-alignment.o
test-parsimony: test-parsimony.c ../sequence-alignment/sequence-alignment.o ../tree/tree.o ../eval/parsimony.o

debug: CFLAGS += -g -DDEBUG
debug: all

profile: CFLAGS += -pg
profile: all

clean:
	rm -f $(OBJECTS) $(EXECUTABLES)
