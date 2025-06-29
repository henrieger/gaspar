CC = gcc
CFLAGS = -Wall -I.. -march=native
LDLIBS =
OBJECTS = *.o

all: ${OBJECTS}
math.o: math.c math.h

optimize: CFLAGS += -O3
optimize: all

debug: CFLAGS += -g -DDEBUG -fsanitize=address
debug: all

profile: CFLAGS += -pg -O0
profile: all

clean:
	rm -f $(OBJECTS)
