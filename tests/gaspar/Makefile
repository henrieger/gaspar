CC = gcc
LDLIBS = -lm
SUBDIRS = eval/ sequence-alignment/ tree/ answer/ search/ operators/ support/ base/
CFLAGS = -g -Wall -I../src -march=native
TARGETS = 

all: $(SUBDIRS)
.PHONY: all $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@ $(TARGETS)
