#ifndef __ANSWER_H__
#define __ANSWER_H__

#include <tree/tree.h>

typedef struct answer {
  int numTrees;
  int currTree;
  tree_t **trees;
  unsigned int score;
} answer_t;

// Initialize answer structure
answer_t *initializeAnswer(int numTrees);

// Update the answer based on tree and score provided
void updateAnswer(answer_t *answer, tree_t *tree, int score);

// Returns score of answer
unsigned int getScore(answer_t *answer);

// Print information of answer
void printAnswer(answer_t *answer);

// Destroy the answer
void destroyAnswer(answer_t *answer);

#endif // !__ANSWER_H__
