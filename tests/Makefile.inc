GASPAR_LIB_PREFIX = ../../lib

GASPAR_LIB_C_FILES = \
	$(GASPAR_LIB_PREFIX)/answer/answer.c \
	$(GASPAR_LIB_PREFIX)/base/config.c \
	$(GASPAR_LIB_PREFIX)/eval/parsimony.c \
	$(GASPAR_LIB_PREFIX)/operators/hybrid.c \
	$(GASPAR_LIB_PREFIX)/operators/nni.c \
	$(GASPAR_LIB_PREFIX)/operators/spr.c \
	$(GASPAR_LIB_PREFIX)/operators/subtree-swap.c \
	$(GASPAR_LIB_PREFIX)/search/branch-and-bound.c \
	$(GASPAR_LIB_PREFIX)/search/genetic-algorithm.c \
	$(GASPAR_LIB_PREFIX)/search/hill-climbing.c \
	$(GASPAR_LIB_PREFIX)/sequence-alignment/sequence-alignment.c \
	$(GASPAR_LIB_PREFIX)/support/bootstrap.c \
	$(GASPAR_LIB_PREFIX)/tree/iterator.c \
	$(GASPAR_LIB_PREFIX)/tree/random.c \
	$(GASPAR_LIB_PREFIX)/tree/tree.c \
	$(GASPAR_LIB_PREFIX)/utils/math.c

GASPAR_LIB_H_FILES = \
	$(GASPAR_LIB_PREFIX)/answer/answer.h \
	$(GASPAR_LIB_PREFIX)/base/config.h \
	$(GASPAR_LIB_PREFIX)/eval/parsimony.h \
	$(GASPAR_LIB_PREFIX)/operators/hybrid.h \
	$(GASPAR_LIB_PREFIX)/operators/nni.h \
	$(GASPAR_LIB_PREFIX)/operators/spr.h \
	$(GASPAR_LIB_PREFIX)/operators/subtree-swap.h \
	$(GASPAR_LIB_PREFIX)/search/branch-and-bound.h \
	$(GASPAR_LIB_PREFIX)/search/genetic-algorithm.h \
	$(GASPAR_LIB_PREFIX)/search/hill-climbing.h \
	$(GASPAR_LIB_PREFIX)/sequence-alignment/sequence-alignment.h \
	$(GASPAR_LIB_PREFIX)/support/bootstrap.h \
	$(GASPAR_LIB_PREFIX)/tree/iterator.h \
	$(GASPAR_LIB_PREFIX)/tree/random.h \
	$(GASPAR_LIB_PREFIX)/tree/tree.h \
	$(GASPAR_LIB_PREFIX)/utils/math.h
