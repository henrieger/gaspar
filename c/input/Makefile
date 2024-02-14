CC = gcc
CFLAGS = -Wall
LDLIBS = -ll -ly -lc

all: input

input: lex.yy.c inputfile.tab.c inputfile.o inputfile.h ../sequence-alignment.o
	${CC} ${CFLAGS} lex.yy.c inputfile.tab.c inputfile.o ../sequence-alignment.o -o gaspar ${LDLIBS}

lex.yy.c: inputfile.l inputfile.h
	flex inputfile.l

inputfile.tab.c: inputfile.y inputfile.h
	bison inputfile.y -d -v

inputfile.o: inputfileF.c inputfile.h
	${CC} ${CFLAGS} -c inputfileF.c -o inputfile.o

debug: CFLAGS += -g -DDEBUG
debug: all

clean:
	rm -f *.o lex.yy.c inputfile.tab.* inputfile.output
