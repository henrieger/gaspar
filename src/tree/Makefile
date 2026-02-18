CC = gcc
CFLAGS = -Wall -I..
LDLIBS = 
OBJECTS = tree.o random.o iterator.o

all: $(OBJECTS)
tree.o: tree.c tree.h
random.o: random.c random.h
iterator.o: iterator.c iterator.h

optimize: CFLAGS += -O3
optimize: all

debug: CFLAGS += -g -DDEBUG
debug: all

sanitize: CFLAGS += -g -fsanitize=address
sanitize: all

profile: CFLAGS += -pg -O0
profile: all

clean:
	rm -f $(OBJECTS)
