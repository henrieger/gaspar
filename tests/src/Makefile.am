include ../Makefile.inc

check_PROGRAMS = functions

functions_SOURCES = \
	functions.c \
	../../src/functions.c \
	../../src/functions.h \
	$(GASPAR_LIB_C_FILES) \
	$(GASPAR_LIB_H_FILES)

TESTS = $(check_PROGRAMS)

AM_CPPFLAGS = -I../../lib -I../../src
