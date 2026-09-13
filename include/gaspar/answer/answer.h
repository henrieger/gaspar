#ifndef __ANSWER_H__
#define __ANSWER_H__

#include <gaspar/sequence-alignment/sequence-alignment.h>
#include <gaspar/tree/tree.h>

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

typedef struct answer {
  uint32_t numTrees;
  uint32_t currTree;
  tree_t *trees;
  double score;
} answer_t;

// Initialize answer structure.
answer_t *initializeAnswer(uint32_t numTrees, alignment_t *alignment);

// Return number of trees currently in the answer.
uint32_t getNumberOfTrees(answer_t *answer);

// Update the answer based on tree and score provided.
void updateAnswer(answer_t *answer, tree_t *tree, double score);

// Returns score of answer.
double getScore(answer_t *answer);

// Print information of answer.
uint64_t printAnswer(answer_t *answer, char *buffer, size_t size);

// Destroy the answer.
void destroyAnswer(answer_t *answer);

#endif // !__ANSWER_H__
