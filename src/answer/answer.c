#include "answer.h"
#include <stdio.h>
#include <stdlib.h>
#include <tree/tree.h>

// Initialize answer structure.
answer_t *initializeAnswer(int numTrees) {
  answer_t *answer = malloc(sizeof(answer_t));
  answer->numTrees = numTrees;
  answer->trees = calloc(numTrees, sizeof(tree_t *));
  answer->currTree = 0;
  answer->score = -1;
  return answer;
}

// Return number of trees currently in the answer.
inline int getNumberOfTrees(answer_t *answer) {
  return answer->currTree;
}

// Insert a new tree in the answer if there is available space.
void insertAnswer(answer_t *answer, tree_t *tree) {
  if (answer->currTree < 0 || answer->currTree >= answer->numTrees)
    return;

  answer->trees[answer->currTree] = copyTree(tree);
  answer->currTree++;
}

// Delete all trees in answer and sets new score of answer.
void resetAndUpdateScore(answer_t *answer, int newScore) {
  answer->score = newScore;
  answer->currTree = 0;
  for (int i = 0; i < answer->numTrees; i++) {
    destroyTree(answer->trees[i]);
    answer->trees[i] = NULL;
  }
}

void updateAnswer(answer_t *answer, tree_t *tree, int score) {
  if (score > getScore(answer))
    return;
#ifdef DEBUG
  printf("New score : %d - Curr score: %d\n", score, getScore(answer));
#endif
  if (score < getScore(answer))
    resetAndUpdateScore(answer, score);

  for (int i = 0; i < answer->currTree; i++) {
    if (areEqual(tree, answer->trees[i]))
      return;
  }

  insertAnswer(answer, tree);
}

// Returns score of answer
unsigned int getScore(answer_t *answer) { return answer->score; }

// Print information of answer
void printAnswer(answer_t *answer, FILE *fp) {
  FILE *finalFile = fp;
  if (!fp)
    finalFile = stdout;

  fprintf(finalFile, "-- ANSWER --\nMin score: %u\nTrees: %d\n", getScore(answer), answer->currTree);
  if (answer->currTree < 16)
    for (int i = 0; answer->trees[i] && i < answer->numTrees; i++) {
      fprintf(finalFile, "\t");

#ifdef DEBUG
    printTree(answer->trees[i]);
#endif /* ifdef DEBUG */

    printNewick(answer->trees[i], finalFile);
    fprintf(finalFile, ";\n");
  }
}

// Destroy the answer
void destroyAnswer(answer_t *answer) {
  resetAndUpdateScore(answer, 0);
  free(answer->trees);
  free(answer);
}
