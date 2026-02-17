CC = gcc
LDLIBS = -lm
OBJECTS = *.o
# SUBDIRS = eval/ sequence-alignment/ tree/ answer/ search/ operators/ support/ utils/
SUBDIRS = sequence-alignment/ tree/ eval
CFLAGS = -g -Wall -I../src -march=native
TARGETS = 

all: $(SUBDIRS) run clean
.PHONY: all $(SUBDIRS)

config: config.o ../src/config.o ../src/eval/parsimony.o ../src/operators/spr.o ../src/sequence-alignment/sequence-alignment.o ../src/sequence-alignment/mask-operations.o ../src/utils/math.o ../src/tree/tree.o ../src/tree/iterator.o ../src/tree/random.o ../src/search/genetic-algorithm.o ../src/answer/answer.o
config.o: config.c

gaspar: gaspar.o ../src/gaspar.o ../src/config.o ../src/eval/parsimony.o ../src/operators/spr.o ../src/sequence-alignment/sequence-alignment.o ../src/sequence-alignment/mask-operations.o ../src/utils/math.o ../src/tree/tree.o ../src/tree/iterator.o ../src/tree/random.o ../src/search/genetic-algorithm.o ../src/answer/answer.o
gaspar.o: gaspar.c

run: config gaspar
	valgrind ./config
	valgrind ./gaspar

clean:
	rm -f config gaspar $(OBJECTS)

$(SUBDIRS):
	$(MAKE) -C $@ $(TARGETS)
