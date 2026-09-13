INCLUDE_DIR = ../../../include
CC = gcc
CFLAGS = -Wall -I${INCLUDE_DIR}
LDLIBS = 
OBJECTS = *.o

all: answer.o
answer.o: answer.c ${INCLUDE_DIR}/gaspar/answer/answer.h

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
