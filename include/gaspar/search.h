#ifndef __LIBGASPAR_SEARCH_H__
#define __LIBGASPAR_SEARCH_H__

#include <gaspar/answer.h>
#include <gaspar/config.h>
#include <gaspar/sequence-alignment.h>
#include <gaspar/tree.h>

// Performs a branch and bound search with given alignment and eval function
answer_t *branchAndBoundSearch(alignment_t *alignment, config_t *config);

// Perform a search using a hill climbing optimization algorithm
answer_t *hillClimbingSearch(alignment_t *alignment, config_t *config);

// Perform a search using a genetic algorithm.
answer_t *geneticAlgorithmSearch(alignment_t *alignment, config_t *config);

#endif // !__LIBGASPAR_SEARCH_H__
