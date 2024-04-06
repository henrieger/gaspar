CC = gcc
CFLAGS = -g -Wall -I.. -O3
LDLIBS = 
OBJECTS = tree.o random.o

all: $(OBJECTS)
tree.o: tree.c tree.h
random.o: random.c random.h

debug: CFLAGS += -g -DDEBUG
debug: all

profile: CFLAGS += -pg
profile: all

clean:
	rm -f $(OBJECTS)
