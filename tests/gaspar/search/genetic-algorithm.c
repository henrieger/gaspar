#include <gaspar/search/genetic-algorithm.h>

#include <gaspar/answer/answer.h>
#include <gaspar/base/config.h>
#include <gaspar/eval/parsimony.h>
#include <gaspar/operators/hybrid.h>
#include <gaspar/operators/nni.h>
#include <gaspar/operators/spr.h>
#include <gaspar/operators/subtree-swap.h>
#include <gaspar/sequence-alignment/sequence-alignment.h>

#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include "correct-tree.h"

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

  config_t config = {.ga_generations = 1000,
                     .ga_generationCuttof = 100,
                     .ga_mutationOperator = randomNNI,
                     .ga_populationSize = 8,
                     .searchMethod = geneticAlgorithmSearch,
                     .evalFn = fitchParsimony,
                     .answer_size = 100};

  srand(2001);

  for (int i = 0; i < alignment->characters; i++) {
    alignment->weights[i] = 1;
  }
  calculateCumulativeWeights(alignment);

  // test createGenerationBests and resetGenerationBests
  createGenerationBests(&config);
  for (int i = 0; i < config.ga_generations; i++) {
    assert(generationBest[i] == -1);
  }

  char buffer[1024];

  // Test genetic algorithm search using NNI as mutation
  answer_t *answer = geneticAlgorithmSearch(alignment, &config);
  printAnswer(answer, buffer, 1024);
  printf("%s\n", buffer);
  assert(answer->score == 8);
  for (int i = 0; i < answer->currTree; i++) {
    assertTreeCorrectness(answer->trees + i);
  }
  destroyAnswer(answer);

  // Test genetic algorithm search using SPR as mutation
  resetGenerationBests(&config);
  config.ga_mutationOperator = randomSPR;
  answer = geneticAlgorithmSearch(alignment, &config);
  printAnswer(answer, buffer, 1024);
  printf("%s\n", buffer);
  assert(answer->score == 8);
  for (int i = 0; i < answer->currTree; i++) {
    assertTreeCorrectness(answer->trees + i);
  }
  destroyAnswer(answer);

  // Test genetic algorithm search using hybrid mutation
  resetGenerationBests(&config);
  config.ga_mutationOperator = hybridOp;
  config.hybrid_nniProb = 0.8;
  answer = geneticAlgorithmSearch(alignment, &config);
  printAnswer(answer, buffer, 1024);
  printf("%s\n", buffer);
  assert(answer->score == 8);
  for (int i = 0; i < answer->currTree; i++) {
    assertTreeCorrectness(answer->trees + i);
  }
  destroyAnswer(answer);

  // Test genetic algorithm search using Subtree-Swap as mutation
  resetGenerationBests(&config);
  config.ga_mutationOperator = randomSubtreeSwap;
  answer = geneticAlgorithmSearch(alignment, &config);
  printAnswer(answer, buffer, 1024);
  printf("%s\n", buffer);
  assert(answer->score == 8);
  for (int i = 0; i < answer->currTree; i++) {
    assertTreeCorrectness(answer->trees + i);
  }
  destroyAnswer(answer);

  destroyGenerationBests(&config);
  destroyAlignment(alignment);

  return 0;
}
