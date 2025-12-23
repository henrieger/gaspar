CC = gcc
CFLAGS = -Wall -I.. -march=native
LDLIBS = 
OBJECTS = *.o

all: sequence-alignment.o mask-operations.o
sequence-alignment.o: sequence-alignment.c sequence-alignment.h
mask-operations.o: mask-operations.c mask-operations.h sequence-alignment.o

optimize: CFLAGS += -O3
optimize: all

debug: CFLAGS += -g -DDEBUG
debug: all

sanitize: CFLAGS += -fsanitize=address
sanitize: debug

profile: CFLAGS += -pg -O0
profile: all

clean:
	rm -f $(OBJECTS)
