INCLUDE_DIR = ../../include
CC = gcc
LDLIBS = -lfl -ly -lc -lm
OBJECTS = */*.o
EXECUTABLE = gaspar
SUBDIRS = eval/ sequence-alignment/ tree/ answer/ search/ operators/ support/ utils/ base/
CFLAGS = -Wall -I${INCLUDE_DIR} -march=native
TARGETS = 

all: $(SUBDIRS) gaspar
.PHONY: all $(SUBDIRS)

# -- MAIN FILES --
gaspar: lex.yy.c gaspar.tab.c $(SUBDIRS)
	${CC} ${CFLAGS} lex.yy.c gaspar.tab.c $(OBJECTS) -o gaspar ${LDLIBS}

lex.yy.c: gaspar.l ${INCLUDE_DIR}/gaspar/base/functions.h
	flex gaspar.l

gaspar.tab.c: gaspar.y ${INCLUDE_DIR}/gaspar/base/functions.h
	bison gaspar.y -d -v -Wcounterexamples

# -- SUBDIRS --
$(SUBDIRS):
	$(MAKE) -C $@ $(TARGETS)

# -- AUXILIARY RULES --
optimize: TARGETS += optimize
optimize: all

debug: CFLAGS += -g -DDEBUG
debug: TARGETS += debug
debug: all

sanitize: CFLAGS += -g -fsanitize=address
sanitize: TARGETS += sanitize
sanitize: all

profile: CFLAGS += -pg -O0
profile: TARGETS += profile
profile: all

clean: TARGETS += clean
clean: $(SUBDIRS)
	rm -f $(OBJECTS) lex.yy.c gaspar.tab.* gaspar.output $(EXECUTABLE)
