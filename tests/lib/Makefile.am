include ../Makefile.inc

check_PROGRAMS = \
	answer/answer \
	base/config \
	eval/parsimony \
	operators/hybrid \
	operators/nni \
	operators/spr \
	operators/subtree-swap \
	search/branch-and-bound \
	search/genetic-algorithm \
	search/hill-climbing \
	sequence-alignment/sequence-alignment \
	support/bootstrap \
	tree/iterator \
	tree/random \
	tree/tree

SEARCH_CORRECT_TREE_FILES = search/correct-tree.c search/correct-tree.h

answer_answer_SOURCES = answer/answer.c $(GASPAR_LIB_C_FILES) $(GASPAR_LIB_H_FILES)
base_config_SOURCES = base/config.c $(GASPAR_LIB_C_FILES) $(GASPAR_LIB_H_FILES)
eval_parsimony_SOURCES = eval/parsimony.c $(GASPAR_LIB_C_FILES) $(GASPAR_LIB_H_FILES)
operators_hybrid_SOURCES = operators/hybrid.c $(GASPAR_LIB_C_FILES) $(GASPAR_LIB_H_FILES)
operators_nni_SOURCES = operators/nni.c $(GASPAR_LIB_C_FILES) $(GASPAR_LIB_H_FILES)
operators_spr_SOURCES = operators/spr.c $(GASPAR_LIB_C_FILES) $(GASPAR_LIB_H_FILES)
operators_subtree_swap_SOURCES = operators/subtree-swap.c $(GASPAR_LIB_C_FILES) $(GASPAR_LIB_H_FILES)
search_branch_and_bound_SOURCES = search/branch-and-bound.c $(GASPAR_LIB_C_FILES) $(GASPAR_LIB_H_FILES) $(SEARCH_CORRECT_TREE_FILES)
search_genetic_algorithm_SOURCES = search/genetic-algorithm.c $(GASPAR_LIB_C_FILES) $(GASPAR_LIB_H_FILES) $(SEARCH_CORRECT_TREE_FILES)
search_hill_climbing_SOURCES = search/hill-climbing.c $(GASPAR_LIB_C_FILES) $(GASPAR_LIB_H_FILES) $(SEARCH_CORRECT_TREE_FILES)
sequence_alignment_sequence_alignment_SOURCES = sequence-alignment/sequence-alignment.c $(GASPAR_LIB_C_FILES) $(GASPAR_LIB_H_FILES)
support_bootstrap_SOURCES = support/bootstrap.c $(GASPAR_LIB_C_FILES) $(GASPAR_LIB_H_FILES)
tree_iterator_SOURCES = tree/iterator.c $(GASPAR_LIB_C_FILES) $(GASPAR_LIB_H_FILES)
tree_random_SOURCES = tree/random.c $(GASPAR_LIB_C_FILES) $(GASPAR_LIB_H_FILES)
tree_tree_SOURCES = tree/tree.c $(GASPAR_LIB_C_FILES) $(GASPAR_LIB_H_FILES)

TESTS = $(check_PROGRAMS)

AM_CPPFLAGS = -I../../lib
