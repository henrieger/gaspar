#ifndef __GENETIC_ALGORITHM_H__
#define __GENETIC_ALGORITHM_H__

#include <answer/answer.h>
#include <config.h>
#include <sequence-alignment/sequence-alignment.h>
#include <tree/tree.h>

extern int *generationBest; // Array with the best score in each generation

// Allocate array of generation bests
void createGenerationBests(config_t *config);

// Reset array of generation bests
void resetGenerationBests(config_t *config);

// Destroy array of generation bests
void destroyGenerationBests(config_t *config);

// Perform a search using a genetic algorithm.
answer_t *geneticAlgorithmSearch(alignment_t *alignment, config_t *config);

#endif // !__GENETIC_ALGORITHM_H__
