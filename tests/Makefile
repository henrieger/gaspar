CC = gcc
LDLIBS = 
OBJECTS = 
# SUBDIRS = eval/ sequence-alignment/ tree/ answer/ search/ operators/ support/ utils/
SUBDIRS = sequence-alignment/
CFLAGS = -Wall -I../src -march=native
TARGETS = 

all: $(SUBDIRS)
.PHONY: all $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@ $(TARGETS)
