CC = gcc
CFLAGS = -Wall -I.. -march=native
LDLIBS =
OBJECTS = math.o

all: ${OBJECTS}
math.o: math.c math.h

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
