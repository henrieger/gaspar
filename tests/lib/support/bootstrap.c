#include <gaspar/support/bootstrap.h>

#include <gaspar/answer/answer.h>
#include <gaspar/base/config.h>
#include <gaspar/eval/parsimony.h>
#include <gaspar/operators/spr.h>
#include <gaspar/search/genetic-algorithm.h>
#include <gaspar/sequence-alignment/sequence-alignment.h>

#include <assert.h>
#include <stdint.h>

int main() {
  // Alignment data for this test is taken from the book
  // Inferring Phylogenies (Felsenstein, 2004)
  // Alignment:
  // Alpha    100110
  // Beta     001000
  // Gamma    110000
  // Delta    110111
  // Epsilon  001110

  const uint64_t taxa = 5;
  const uint64_t characters = 6;
  const uint64_t states = 2;
  char *labels[] = {"Alpha", "Beta", "Gamma", "Delta", "Epsilon"};

  alignment_t *alignment = newAlignment(taxa, characters, states, labels);

  // Alpha
  alignment->sequenceMasks[0][0][0] = 0x26;
  alignment->sequenceMasks[0][1][0] = 0x19;

  // Beta
  alignment->sequenceMasks[1][0][0] = 0x3b;
  alignment->sequenceMasks[1][1][0] = 0x04;

  // Gamma
  alignment->sequenceMasks[2][0][0] = 0x3c;
  alignment->sequenceMasks[2][1][0] = 0x03;

  // Delta
  alignment->sequenceMasks[3][0][0] = 0x04;
  alignment->sequenceMasks[3][1][0] = 0x3b;

  // Epsilon
  alignment->sequenceMasks[4][0][0] = 0x23;
  alignment->sequenceMasks[4][1][0] = 0x1c;

  config_t config;
  setConfigsToDefault(&config);
  config.ga_generations = 1000;
  config.ga_generationCuttof = 100;
  config.answer_size = 100;
  config.bs_replicates = 10;

  // Test genetic algorithm search using NNI as mutation
  bootstrap(alignment, &config);

  destroyAlignment(alignment);

  return 0;
}
