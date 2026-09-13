INCLUDE_DIR = ../../../include
CC = gcc
CFLAGS = -Wall -I${INCLUDE_DIR}
LDLIBS =
OBJECTS = config.o functions.o

all: $(OBJECTS)
config.o: config.c ${INCLUDE_DIR}/gaspar/base/config.h
functions.o: functions.c ${INCLUDE_DIR}/gaspar/base/functions.h

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
