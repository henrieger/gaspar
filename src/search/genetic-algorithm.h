#ifndef __GENETIC_ALGORITHM_H__
#define __GENETIC_ALGORITHM_H__

#include <answer/answer.h>
#include <config.h>
#include <sequence-alignment/sequence-alignment.h>
#include <tree/tree.h>

// Perform a search using a genetic algorithm.
answer_t *geneticAlgorithmSearch(alignment_t *alignment, config_t *config);

#endif // !__GENETIC_ALGORITHM_H__
