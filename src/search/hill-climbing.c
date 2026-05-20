#include "hill-climbing.h"

#include <answer/answer.h>
#include <config.h>
#include <operators/nni.h>
#include <operators/spr.h>
#include <operators/subtree-swap.h>
#include <sequence-alignment/sequence-alignment.h>
#include <stdint.h>
#include <tree/iterator.h>
#include <tree/random.h>
#include <tree/tree.h>

void nniCycle(tree_t *tree, double score, config_t *config, answer_t *answer) {
  double bestScore = score;
  uint32_t bestN1 = NULL_EDGE;
  uint32_t bestN2 = NULL_EDGE;
  int bestJoint = 0;

  treeIterator *it = newSubtreeIterator(tree, tree->right[0]);
  do {
    score = bestScore;
    bestN1 = bestN2 = NULL_EDGE;

#ifdef DEBUG
    printf("Best score: %lf\n", score);
#endif /* ifdef DEBUG */

    for (int32_t node = nextTreeIterator(it); node != NULL_EDGE;
         node = nextTreeIterator(it)) {
      if (node >= treeLeaves(tree))
        continue;

      double treeScore;
      uint32_t n1 = tree->parent[node];
      uint32_t n2 = node;

      nni(tree, n1, n2, 0);
      treeScore = config->evalFn(tree, config);
      if (treeScore < getScore(answer)) {
        bestN1 = n1;
        bestN2 = n2;
        bestJoint = 0;
        bestScore = treeScore;
        updateAnswer(answer, tree, treeScore);
      }
      nni(tree, n1, n2, 0);

      nni(tree, n1, n2, 1);
      treeScore = config->evalFn(tree, config);
      if (treeScore < bestScore) {
        bestN1 = n1;
        bestN2 = n2;
        bestJoint = 1;
        bestScore = treeScore;
        updateAnswer(answer, tree, treeScore);
      }
      nni(tree, n1, n2, 1);
    }

    if (bestScore < score) {
      nni(tree, bestN1, bestN2, bestJoint);
    }
    resetTreeIterator(it);
  } while (bestScore < score);
  destroyIterator(it);
}

void graftRecursive(tree_t *tree, config_t *config, uint32_t p1, uint32_t p2,
                    double *bestScore, int32_t *bestP1, int32_t *bestP2,
                    int32_t *bestG1, int32_t *bestG2) {
  treeIterator *it = newSubtreeIterator(tree, tree->right[0]);
  nextTreeIterator(it);
  for (int32_t g2 = nextTreeIterator(it); g2 != NULL_EDGE;
       g2 = nextTreeIterator(it)) {
    int32_t g1 = tree->parent[g2];
    subtreeGraft(tree, p1, p2, g1, g2);
    double score = config->evalFn(tree, config);
#ifdef DEBUG
    printf("\tgrafting onto %d - %d: score %lf\n", g1, g2, score);
#endif /* ifdef DEBUG*/
    if (score < *bestScore) {
      *bestScore = score;
      *bestP1 = p1;
      *bestP2 = p2;
      *bestG1 = g1;
      *bestG2 = g2;
    }
    subtreePrune(tree, p1, p2);
  }
  destroyIterator(it);
}

void sprCycle(tree_t *tree, double score, config_t *config, answer_t *answer) {
  double bestScore = score;
  int32_t bestP1, bestP2, bestG1, bestG2;
  bestP1 = bestP2 = bestG1 = bestG2 = NULL_EDGE;

  treeIterator *it = newSubtreeIterator(tree, tree->right[0]);
  uint32_t p1, p2, oldG1, oldG2;

  do {
#ifdef DEBUG
    printTree(tree);
#endif /* ifdef DEBUG */
    score = bestScore;

    for (p2 = nextTreeIterator(it); p2 != NULL_EDGE;
         p2 = nextTreeIterator(it)) {
      p1 = tree->parent[p2];

      if (p1 == tree->right[0] || p2 == tree->right[0]) {
        continue;
      }

      oldG1 = tree->parent[p1];
      if (tree->left[p1] == p2) {
        oldG2 = tree->right[p1];
      } else {
        oldG2 = tree->left[p1];
      }

#ifdef DEBUG
      printf("Pruning subtree %d - %d\n", p1, p2);
#endif /* ifdef DEBUG */
      subtreePrune(tree, p1, p2);
      graftRecursive(tree, config, p1, p2, &bestScore, &bestP1, &bestP2,
                     &bestG1, &bestG2);
      subtreeGraft(tree, p1, p2, oldG1, oldG2);
    }

    if (bestScore < score) {
      subtreePrune(tree, bestP1, bestP2);
      subtreeGraft(tree, bestP1, bestP2, bestG1, bestG2);
      updateAnswer(answer, tree, bestScore);
    }

#ifdef DEBUG
    char buffer[LABEL_SIZE * LABEL_SIZE];
    printNewick(tree, buffer);
    printf("New tree: %s - Score %lf\n", buffer, bestScore);
#endif /* ifdef DEBUG */

    resetTreeIterator(it);
  } while (bestScore < score);
  destroyIterator(it);
}

void subtreeSwapCycle(tree_t *tree, double score, config_t *config,
                      answer_t *answer) {
  double bestScore = score;
  int32_t bestN1 = NULL_EDGE;
  int32_t bestN2 = NULL_EDGE;

  treeIterator *externalIt = newSubtreeIterator(tree, tree->right[0]);
  treeIterator *internalIt = newSubtreeIterator(tree, tree->right[0]);
  do {
    score = bestScore;
    bestN1 = bestN2 = NULL_EDGE;

#ifdef DEBUG
    printf("Best score: %lf\n", score);
#endif /* ifdef DEBUG */

    resetTreeIterator(externalIt);
    for (int32_t n1 = nextTreeIterator(externalIt); n1 != NULL_EDGE;
         n1 = nextTreeIterator(externalIt)) {
      if (n1 == tree->right[0] || n1 == 0)
        continue;

      double treeScore;

      resetTreeIterator(internalIt);
      for (int32_t n2 = nextTreeIterator(internalIt); n2 != NULL_EDGE;
           n2 = nextTreeIterator(internalIt)) {
        if (n2 == 0 || n2 == tree->right[0] || isAncestor(tree, n1, n2) ||
            isAncestor(tree, n2, n1)) {
          continue;
        }

        subtreeSwap(tree, n1, n2);
        treeScore = config->evalFn(tree, config);
        if (treeScore < getScore(answer)) {
          bestN1 = n1;
          bestN2 = n1;
          bestScore = treeScore;
          updateAnswer(answer, tree, treeScore);
        }
        subtreeSwap(tree, n1, n2);
      }
    }

    if (bestScore < score) {
      subtreeSwap(tree, bestN1, bestN2);
    }
  } while (bestScore < score);
  destroyIterator(externalIt);
  destroyIterator(internalIt);
}

// Single replicate of hill climbing search returning one optimal tree
tree_t *hillClimbingReplicate(alignment_t *alignment, config_t *config,
                              answer_t *answer) {
  // Initialize a random tree
  tree_t *tree = newTree(alignment);
  randomTree(tree);
  int score = config->evalFn(tree, config);

#ifdef DEBUG
  printf("Starting with tree:\n");
  printTree(tree);
#endif /* ifdef DEBUG */

  switch (config->hc_operator) {
  case NNI:
    nniCycle(tree, score, config, answer);
    break;
  case SPR:
    sprCycle(tree, score, config, answer);
    break;
  case SUBTREE_SWAP:
    subtreeSwapCycle(tree, score, config, answer);
    break;
  }

  return tree;
}

// Perform a search using a hill climbing optimization algorithm
answer_t *hillClimbingSearch(alignment_t *alignment, config_t *config) {
  answer_t *answer = initializeAnswer(config->answer_size, alignment);

  for (int i = 0; i < config->hc_replicates; i++) {
#ifdef DEBUG
    printf("-- HC Replicate %d --\n", i + 1);
#endif /* ifdef DEBUG */
    tree_t *tree = hillClimbingReplicate(alignment, config, answer);
    destroyTree(tree);
  }

  return answer;
}
