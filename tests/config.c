#include <assert.h>
#include <config.h>
#include <eval/parsimony.h>
#include <operators/spr.h>
#include <search/genetic-algorithm.h>
#include <string.h>

int main() {
  config_t config = {};

  setConfigsToDefault(&config);

  // assert(config.name == NULL);
  assert(config.searchMethod == geneticAlgorithmSearch);
  assert(config.evalFn == fitchParsimony);
  assert(config.answer_size == 10000);
  assert(config.hc_operator == NNI);
  assert(config.hc_replicates == 8);
  assert(config.ga_mutationOperator == randomSPR);
  // assert(config.ga_recombinationOperator == NULL);
  assert(config.ga_populationSize == 8);
  assert(config.ga_generations == 1000000);
  assert(config.ga_generationCuttof == 20000);
  assert(config.ga_selectionStrength == 0.5);
  assert(config.spr_probability == 0.05);
  assert(config.hybrid_nniProb == 0.8);
  assert(config.bs_replicates == 100);

  setName(&config, "Test");
  assert(!strcmp(config.name, "Test"));
}
