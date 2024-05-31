CC = gcc
CFLAGS = -Wall -I..
LDLIBS = 
OBJECTS = tree.o random.o

all: $(OBJECTS)
tree.o: tree.c tree.h
random.o: random.c random.h

optimize: CFLAGS += -O3
optimize: all

debug: CFLAGS += -g -DDEBUG
debug: all

profile: CFLAGS += -pg -O0
profile: all

clean:
	rm -f $(OBJECTS)
