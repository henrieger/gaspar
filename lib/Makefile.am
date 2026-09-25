AUTOMAKE_OPTIONS = foreign

ANSWER_FILES = answer/answer.c answer/answer.h

BASE_FILES = base/config.c base/config.h

EVAL_FILES = eval/parsimony.c eval/parsimony.h

OPERATORS_CFILES = \
	operators/nni.c \
	operators/spr.c \
	operators/subtree-swap.c \
	operators/hybrid.c
OPERATORS_HFILES = \
	operators/nni.h \
	operators/spr.h \
	operators/subtree-swap.h \
	operators/hybrid.h
OPERATORS_FILES = $(OPERATORS_CFILES) $(OPERATORS_HFILES)

SEARCH_CFILES = \
	search/branch-and-bound.c \
	search/hill-climbing.c \
	search/genetic-algorithm.c
SEARCH_HFILES = \
	search/branch-and-bound.h \
	search/hill-climbing.h \
	search/genetic-algorithm.h
SEARCH_FILES = $(SEARCH_CFILES) $(SEARCH_HFILES)

SEQUENCE_ALIGNMENT_FILES = \
	sequence-alignment/sequence-alignment.c \
	sequence-alignment/sequence-alignment.h

SUPPORT_FILES = support/bootstrap.c suppport/bootstrap.h

TREE_CFILES = \
	tree/iterator.c \
	tree/random.c \
	tree/tree.c
TREE_HFILES = \
	tree/iterator.h \
	tree/random.h \
	tree/tree.h
TREE_FILES = $(TREE_CFILES) $(TREE_HFILES)

UTILS_FILES = utils/math.c utils/math.h


LIBGASPAR_FILES = \
	$(ANSWER_FILES) \
	$(BASE_FILES) \
	$(EVAL_FILES) \
	$(OPERATORS_FILES) \
	$(SEARCH_FILES) \
	$(SEQUENCE_ALIGNMENT_FILES) \
	$(SUPPORT_FILES) \
	$(TREE_FILES) \
	$(UTILS_FILES)

lib_LTLIBRARIES = libgaspar.la
libgaspar_la_SOURCES = $(LIBGASPAR_FILES)
libgaspar_la_CFLAGS = -Wall -Wextra
libgaspar_la_LIBS = -lm
