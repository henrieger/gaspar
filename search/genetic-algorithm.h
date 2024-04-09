#ifndef __GENETIC_ALGORITHM_H__
#define __GENETIC_ALGORITHM_H__

#include <answer/answer.h>
#include <sequence-alignment/sequence-alignment.h>
#include <tree/tree.h>

answer_t *geneticAlgorithmSearch(alignment_t alignment, int populationSize,
                                 int generations,
                                 void mutationOperator(node_t *),
                                 int eval_fn(tree_t *));

#endif // !__GENETIC_ALGORITHM_H__
