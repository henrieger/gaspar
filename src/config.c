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
  config->answer_size = 100;
  config->hc_operator = SPR;
  config->hc_replicates = 8;
  config->ga_mutationOperator = randomSPR;
  // config->ga_recombinationOperator = pdr;
  config->ga_populationSize = 8;
  config->ga_generations = 10000;
  config->spr_probability = 0.5;
  config->bs_replicates = 99;
}

// Set the name of the analisys
void setName(config_t *config, char *name) {
  memcpy(config->name, name, LABEL_SIZE);
}
