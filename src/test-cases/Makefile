CC = gcc
CFLAGS = -Wall -I..
OBJECTS = *.o
# EXECUTABLES = test-trees test-sequence-alignment test-parsimony test-operators
EXECUTABLES = test-sequence-alignment test-trees

all: $(EXECUTABLES)

test-trees: test-trees.c ../tree/tree.o ../tree/random.o ../sequence-alignment/sequence-alignment.o
test-operators: test-operators.c ../tree/tree.o ../tree/random.o ../sequence-alignment/sequence-alignment.o ../operators/*.o
test-sequence-alignment: test-sequence-alignment.c ../sequence-alignment/sequence-alignment.o
test-parsimony: test-parsimony.c ../sequence-alignment/sequence-alignment.o ../tree/tree.o ../eval/parsimony.o

debug: CFLAGS += -g -DDEBUG
debug: all

optimize: CFLAGS += -O3
optimze: all

profile: CFLAGS += -pg
profile: all

clean:
	rm -f $(OBJECTS) $(EXECUTABLES)
