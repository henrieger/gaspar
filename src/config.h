#ifndef __CONFIG_H__
#define __CONFIG_H__

#include "answer/answer.h"
#include "sequence-alignment/sequence-alignment.h"
#include "tree/tree.h"

typedef struct config {
  // General params
  answer_t *(*searchMethod)(alignment_t *alignment, struct config *config);
  int (*evalFn)(tree_t *, struct config *config);

  // Answer params
  int answer_size;

  // Hill climbing params
  void (*hc_operator)(tree_t *tree);
  unsigned int hc_replicates;

  // Genetic Algorithm params
  void (*ga_mutationOperator)(tree_t *tree);
  void (*ga_recombinationOperator)(tree_t *tree1, tree_t *tree2);
  unsigned int ga_populationSize;
  unsigned int ga_generations;

  // SPR params
  double spr_probability;

  // Bootstrap params
  unsigned int bs_replicates;
} config_t;

// Set all configurations to a pre-estabilished default
void setConfigsToDefault(config_t *config);

#endif // !__CONFIG_H__
