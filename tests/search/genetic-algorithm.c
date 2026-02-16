#include <answer/answer.h>
#include <assert.h>
#include <config.h>
#include <eval/parsimony.h>
#include <operators/hybrid.h>
#include <operators/nni.h>
#include <operators/spr.h>
#include <search/genetic-algorithm.h>
#include <sequence-alignment/sequence-alignment.h>
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

  config_t config = {.ga_generations = 1000,
                     .ga_generationCuttof = 100,
                     .ga_mutationOperator = randomNNI,
                     .ga_populationSize = 8,
                     .searchMethod = geneticAlgorithmSearch,
                     .evalFn = fitchParsimony,
                     .answer_size = 100};

  // test createGenerationBests and resetGenerationBests
  createGenerationBests(&config);
  for (int i = 0; i < config.ga_generations; i++) {
    assert(generationBest[i] == -1);
  }

  initializeGlobalAuxSequences(characters, states);
  char buffer[1024];

  // Test genetic algorithm search using NNI as mutation
  answer_t *answer = geneticAlgorithmSearch(alignment, &config);
  printAnswer(answer, buffer, 1024);
  printf("%s\n", buffer);
  assert(answer->score == 8);
  assert(getNumberOfTrees(answer) == 1 || getNumberOfTrees(answer) == 2);
  destroyAnswer(answer);

  // Test genetic algorithm search using SPR as mutation
  resetGenerationBests(&config);
  config.ga_mutationOperator = randomSPR;
  answer = geneticAlgorithmSearch(alignment, &config);
  printAnswer(answer, buffer, 1024);
  printf("%s\n", buffer);
  assert(answer->score == 8);
  assert(getNumberOfTrees(answer) == 1 || getNumberOfTrees(answer) == 2);
  destroyAnswer(answer);

  // Test genetic algorithm search using hybrid mutation
  resetGenerationBests(&config);
  config.ga_mutationOperator = hybridOp;
  answer = geneticAlgorithmSearch(alignment, &config);
  printAnswer(answer, buffer, 1024);
  printf("%s\n", buffer);
  assert(answer->score == 8);
  assert(getNumberOfTrees(answer) == 1 || getNumberOfTrees(answer) == 2);
  destroyAnswer(answer);

  destroyGlobalAuxSequences();
  destroyGenerationBests(&config);
  destroyAlignment(alignment);

  return 0;
}
