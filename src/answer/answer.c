#include "answer.h"
#include "sequence-alignment/sequence-alignment.h"
#include <math.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <tree/tree.h>

// Initialize answer structure.
answer_t *initializeAnswer(uint32_t numTrees, alignment_t *alignment) {
  answer_t *answer = malloc(sizeof(answer_t));
  answer->numTrees = numTrees;
  answer->trees = newTreeArray(numTrees, alignment);
  answer->currTree = 0;
  answer->score = INFINITY;
  return answer;
}

// Return number of trees currently in the answer.
inline uint32_t getNumberOfTrees(answer_t *answer) { return answer->currTree; }

// Insert a new tree in the answer if there is available space.
void insertAnswer(answer_t *answer, tree_t *tree) {
  if (answer->currTree < 0 || answer->currTree >= answer->numTrees)
    return;

  copyTree(tree, answer->trees + answer->currTree);
  answer->currTree++;
}

// Delete all trees in answer and sets new score of answer.
void resetAndUpdateScore(answer_t *answer, int newScore) {
  answer->score = newScore;
  answer->currTree = 0;
}

void updateAnswer(answer_t *answer, tree_t *tree, int score) {
  if (score > getScore(answer))
    return;
#ifdef DEBUG
  printf("New score : %d - Curr score: %lf\n", score, getScore(answer));
#endif
  if (score < getScore(answer))
    resetAndUpdateScore(answer, score);

  for (int i = 0; i < answer->currTree; i++) {
    if (areEqual(tree, answer->trees + i))
      return;
  }

  insertAnswer(answer, tree);
}

// Returns score of answer
double getScore(answer_t *answer) { return answer->score; }

// Print information of answer
uint64_t printAnswer(answer_t *answer, char *buffer, size_t size) {
  uint64_t bytesWritten =
      sprintf(buffer, "-- ANSWER --\nMin score: %lf\nTrees: %d\n",
              getScore(answer), getNumberOfTrees(answer));

  for (int i = 0; i < answer->currTree; i++) {
    bytesWritten += sprintf(buffer + bytesWritten, "\t");

#ifdef DEBUG
    printTree(answer->trees + i);
#endif /* ifdef DEBUG */

    bytesWritten += printNewick(answer->trees + i, buffer + bytesWritten);
    bytesWritten += sprintf(buffer + bytesWritten, ";\n");
  }

  return bytesWritten;
}

// Destroy the answer
void destroyAnswer(answer_t *answer) {
  destroyTreeArray(answer->trees);
  free(answer);
}
