CC = gcc
LDLIBS = -ll -ly -lc -lm
OBJECTS = *.o */*.o
EXECUTABLE = gaspar
SUBDIRS = eval/ sequence-alignment/ tree/ answer/ search/ operators/ support/
TESTS = test-cases/
CFLAGS = -Wall -I${CURDIR}
TARGETS = 

all: $(SUBDIRS) gaspar
.PHONY: all $(SUBDIRS) $(TESTS)

# -- MAIN FILES --
gaspar: lex.yy.c gaspar.tab.c gaspar.o config.o gaspar.h $(SUBDIRS)
	${CC} ${CFLAGS} lex.yy.c gaspar.tab.c $(OBJECTS) -o gaspar ${LDLIBS}

lex.yy.c: gaspar.l gaspar.h
	flex gaspar.l

gaspar.tab.c: gaspar.y gaspar.h
	bison gaspar.y -d -v

gaspar.o: gasparFunctions.c gaspar.h
	${CC} ${CFLAGS} -c gasparFunctions.c -o gaspar.o

config.o: config.c config.h

# -- SUBDIRS --
$(SUBDIRS):
	$(MAKE) -C $@ $(TARGETS)

# -- TEST CASES --
test: all $(TESTS)
$(TESTS):
	$(MAKE) -C $@ $(TARGETS)

# -- AUXILIARY RULES --
optimize: TARGETS += optimize
optimize: all

debug: CFLAGS += -g -DDEBUG
debug: TARGETS += debug
debug: all

profile: CFLAGS += -pg -O0
profile: TARGETS += profile
profile: all

clean: TARGETS += clean
clean: $(TESTS) $(SUBDIRS)
	rm -f $(OBJECTS) lex.yy.c gaspar.tab.* gaspar.output $(EXECUTABLE)
