#include "config.h"

#include <string.h>
#include "search/genetic-algorithm.h"
#include "eval/parsimony.h"
#include "operators/spr.h"
#include "sequence-alignment/sequence-alignment.h"

// Set all configurations to a pre-estabilished default 
void setConfigsToDefault(config_t *config) {
  config->name[0] = (char)0;
  config->searchMethod = geneticAlgorithmSearch;
  config->evalFn = fitchParsimony;
  config->answer_size = 10000;
  config->hc_operator = NNI;
  config->hc_replicates = 8;
  config->ga_mutationOperator = randomSPR;
  // config->ga_recombinationOperator = pdr;
  config->ga_populationSize = 8;
  config->ga_generations = 1000000;
  config->ga_generationCuttof = 20000;
  config->ga_selectionStrength = 0.5;
  config->spr_probability = 0.05;
  config->hybrid_nniProb = 0.8;
  config->bs_replicates = 100;
}

// Set the name of the analisys
void setName(config_t *config, char *name) {
  memcpy(config->name, name, LABEL_SIZE);
}
