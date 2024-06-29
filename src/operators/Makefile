CC = gcc
CFLAGS = -Wall -I..
LDLIBS = 
OBJECTS = nni.o spr.o hybrid.o

all: $(OBJECTS)
nni.o: nni.c nni.h
spr.o: spr.c spr.h
hybrid.o: hybrid.c hybrid.h

optimize: CFLAGS += -O3
optimize: all

debug: CFLAGS += -g -DDEBUG
debug: all

profile: CFLAGS += -pg -O0
profile: all

clean:
	rm -f $(OBJECTS)
