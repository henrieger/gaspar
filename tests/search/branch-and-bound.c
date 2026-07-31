#include "correct-tree.h"
#include <answer/answer.h>
#include <assert.h>
#include <config.h>
#include <eval/parsimony.h>
#include <search/branch-and-bound.h>
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

  config_t config = {.searchMethod = branchAndBoundSearch,
                     .evalFn = fitchParsimony,
                     .answer_size = 100};

  for (int i = 0; i < alignment->characters; i++) {
    alignment->weights[i] = 1;
  }
  calculateCumulativeWeights(alignment);
  char buffer[1024];

  // Test branch and bound search using NNI as mutation
  answer_t *answer = branchAndBoundSearch(alignment, &config);
  printAnswer(answer, buffer, 1024);
  printf("%s\n", buffer);
  assert(answer->score == 8);
  assert(getNumberOfTrees(answer) == 1);
  assertTreeCorrectness(answer->trees);
  destroyAnswer(answer);

  destroyAlignment(alignment);

  return 0;
}
