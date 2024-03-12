#include "answer.h"
#include <tree/tree.h>
#include <stdlib.h>
#include <stdio.h>

// Initialize answer structure
answer_t *initializeAnswer(int numTrees) {
  answer_t *answer = malloc(sizeof(answer_t));
  answer->numTrees = numTrees;
  answer->trees = calloc(numTrees, sizeof(tree_t *));
  answer->currTree = 0;
  answer->score = -1;
  return answer;
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

// Returns score of answer
unsigned int getScore(answer_t *answer) {
  return answer->score;
}

// Print information of answer
void printAnswer(answer_t *answer) {
  printf("-- ANSWER --\nMin score: %u\nTrees:\n", getScore(answer));
  for (int i = 0; answer->trees[i] && i < answer->numTrees; i++) {
    printf("\t");
    printTree(answer->trees[i]);
    printf("\n");
  }
}

// Destroy the answer
void destroyAnswer(answer_t *answer) {
  resetAndUpdateScore(answer, 0);
  free(answer->trees);
  free(answer);
}
