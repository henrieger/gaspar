#ifndef __GENETIC_ALGORITHM_H__
#define __GENETIC_ALGORITHM_H__

#include <answer/answer.h>
#include <sequence-alignment/sequence-alignment.h>
#include <tree/tree.h>

// Perform a search using a genetic algorithm.
answer_t *geneticAlgorithmSearch(alignment_t *alignment, int evalFn(tree_t *),
                                 void op(tree_t *), int populationSize,
                                 int generations);

#endif // !__GENETIC_ALGORITHM_H__
