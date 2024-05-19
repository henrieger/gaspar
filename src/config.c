#include "config.h"

#include "search/genetic-algorithm.h"
#include "eval/parsimony.h"
#include "operators/nni.h"
#include "operators/spr.h"

// Set all configurations to a pre-estabilished default 
void setConfigsToDefault(config_t *config) {
  config->searchMethod = geneticAlgorithmSearch;
  config->evalFn = fitchParsimony;
  config->answer_size = 100;
  // config->hc_operator = nni;
  config->hc_replicates = 8;
  config->ga_mutationOperator = randomSPR;
  // config->ga_recombinationOperator = pdr;
  config->ga_populationSize = 8;
  config->ga_generations = 10000;
  config->spr_probability = 0.5;
  config->bs_replicates = 99;
}
