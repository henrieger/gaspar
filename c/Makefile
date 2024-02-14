CC = gcc
LDLIBS = -ll -ly -lc
OBJECTS = *.o */*.o
EXECUTABLE = gaspar
SUBDIRS = eval/ sequence-alignment/ tree/
TESTS = test-cases/
CFLAGS = -Wall -I=${CURDIR}
TARGETS = 

all: $(SUBDIRS) gaspar
.PHONY: all $(SUBDIRS) $(TESTS)

# -- MAIN FILES --
gaspar: lex.yy.c gaspar.tab.c gaspar.o gaspar.h $(SUBDIRS)
	${CC} ${CFLAGS} lex.yy.c gaspar.tab.c $(OBJECTS) -o gaspar ${LDLIBS}

lex.yy.c: gaspar.l gaspar.h
	flex gaspar.l

gaspar.tab.c: gaspar.y gaspar.h
	bison gaspar.y -d -v

gaspar.o: gasparFunctions.c gaspar.h
	${CC} ${CFLAGS} -c gasparFunctions.c -o gaspar.o

# -- SUBDIRS --
$(SUBDIRS):
	$(MAKE) -C $@ $(TARGETS)

# -- TEST CASES --
test: all $(TESTS)
$(TESTS):
	$(MAKE) -C $@ $(TARGETS)

# -- AUXILIARY RULES --
debug: CFLAGS += -g -DDEBUG
debug: TARGETS += debug
debug: all

clean: TARGETS += clean
clean: $(TESTS) $(SUBDIRS)
	rm -f $(OBJECTS) lex.yy.c gaspar.tab.* gaspar.output $(EXECUTABLE)
