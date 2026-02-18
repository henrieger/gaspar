CC = gcc
CFLAGS = -Wall -I..
LDLIBS = 
OBJECTS = *.o

all: bootstrap.o
bootstrap.o: bootstrap.c bootstrap.h

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
