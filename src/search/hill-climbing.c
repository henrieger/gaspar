#include "hill-climbing.h"
#include "operators/spr.h"

#include <answer/answer.h>
#include <config.h>
#include <operators/nni.h>
#include <sequence-alignment/sequence-alignment.h>
#include <stdio.h>
#include <tree/random.h>
#include <tree/tree.h>

void evaluateNNI(tree_t *tree, config_t *config, int n1, int n2, int joint,
                 int *bestN1, int *bestN2, int *bestJoint, int *bestScore) {
#ifdef DEBUG
  printf("NNI between %d and %d (joint %d)\n", n1, n2, joint);
#endif /* ifdef DEBUG */
  nni(tree, n1, n2, joint);
  int score = config->evalFn(tree, config);
  if (score < *bestScore) {
    *bestScore = score;
    *bestN1 = n1;
    *bestN2 = n2;
    *bestJoint = joint;
  }
  nni(tree, n1, n2, joint);
}

void nniCicle(tree_t *tree, int score, config_t *config) {
  int bestScore = score;
  int bestN1 = -1;
  int bestN2 = -1;
  int bestJoint = -1;

  do {
    score = bestScore;

#ifdef DEBUG
    printf("Best score: %d\n", bestScore);
#endif /* ifdef DEBUG */

    for (int i = 0; i < tree->leaves - 2; i++) {
      for (int j = 0; j < 2; j++) {
        if (tree->internal[i].edge1 >= tree->leaves)
          evaluateNNI(tree, config, tree->leaves + i, tree->internal[i].edge1,
                      j, &bestN1, &bestN2, &bestJoint, &bestScore);
        if (tree->internal[i].edge2 >= tree->leaves)
          evaluateNNI(tree, config, tree->leaves + i, tree->internal[i].edge2,
                      j, &bestN1, &bestN2, &bestJoint, &bestScore);
        if (tree->internal[i].edge3 >= tree->leaves)
          evaluateNNI(tree, config, tree->leaves + i, tree->internal[i].edge3,
                      j, &bestN1, &bestN2, &bestJoint, &bestScore);
      }
    }

    if (bestN1 >= 0)
      nni(tree, bestN1, bestN2, bestJoint);

  } while (bestScore < score);
}

void graftRecursive(tree_t *tree, int pruneRoot, int subtree, int left,
                    int right, int *bestScore, int *bestPruneRoot,
                    int *bestSubtree, int *bestGraftNode1, int *bestGraftNode2,
                    config_t *config) {
  int edge1 = tree->nodes[right].edge1;
  int edge2 = tree->nodes[right].edge2;
  int edge3 = tree->nodes[right].edge3;

  if (edge1 > 0 && edge1 != left) {
    subtreeRegraft(tree, pruneRoot, right, edge1);
    int score = config->evalFn(tree, config);
    if (score < *bestScore) {
      *bestScore = score;
      *bestPruneRoot = pruneRoot;
      *bestSubtree = subtree;
      *bestGraftNode1 = right;
      *bestGraftNode2 = edge1;
    }
    subtreePrune(tree, pruneRoot, subtree);
    graftRecursive(tree, pruneRoot, subtree, right, edge1, bestScore,
                   bestPruneRoot, bestSubtree, bestGraftNode1, bestGraftNode2,
                   config);
  }
  if (edge2 > 0 && edge2 != left) {
    subtreeRegraft(tree, pruneRoot, right, edge2);
    int score = config->evalFn(tree, config);
    if (score < *bestScore) {
      *bestScore = score;
      *bestPruneRoot = pruneRoot;
      *bestSubtree = subtree;
      *bestGraftNode1 = right;
      *bestGraftNode2 = edge2;
    }
    subtreePrune(tree, pruneRoot, subtree);
    graftRecursive(tree, pruneRoot, subtree, right, edge2, bestScore,
                   bestPruneRoot, bestSubtree, bestGraftNode1, bestGraftNode2,
                   config);
  }
  if (edge3 > 0 && edge3 != left) {
    subtreeRegraft(tree, pruneRoot, right, edge3);
    int score = config->evalFn(tree, config);
    if (score < *bestScore) {
      *bestScore = score;
      *bestPruneRoot = pruneRoot;
      *bestSubtree = subtree;
      *bestGraftNode1 = right;
      *bestGraftNode2 = edge3;
    }
    subtreePrune(tree, pruneRoot, subtree);
    graftRecursive(tree, pruneRoot, subtree, right, edge3, bestScore,
                   bestPruneRoot, bestSubtree, bestGraftNode1, bestGraftNode2,
                   config);
  }
}

void sprCicle(tree_t *tree, int score, config_t *config) {
  int bestScore = score;
  int bestPruneRoot = -1;
  int bestSubtree = -1;
  int bestGraftNode1 = -1;
  int bestGraftNode2 = -1;

  do {
    score = bestScore;
    int edge1, edge2, edge3;

    for (int i = 0; i < tree->leaves - 2; i++) {
      edge1 = tree->internal[i].edge1;
      edge2 = tree->internal[i].edge2;
      edge3 = tree->internal[i].edge3;

      // Prune and regraft edge1
      if (!isLeaf(tree, edge2) || !isLeaf(tree, edge3)) {
        subtreePrune(tree, i + tree->leaves, edge1);
        graftRecursive(tree, i + tree->leaves, edge1, edge2, edge3, &bestScore,
                       &bestPruneRoot, &bestSubtree, &bestGraftNode1,
                       &bestGraftNode2, config);
        graftRecursive(tree, i + tree->leaves, edge1, edge3, edge2, &bestScore,
                       &bestPruneRoot, &bestSubtree, &bestGraftNode1,
                       &bestGraftNode2, config);
        subtreeRegraft(tree, i + tree->leaves, edge2, edge3);
      }

      // Prune and regraft edge2
      if (!isLeaf(tree, edge1) || !isLeaf(tree, edge3)) {
        subtreePrune(tree, i + tree->leaves, edge2);
        graftRecursive(tree, i + tree->leaves, edge2, edge1, edge3, &bestScore,
                       &bestPruneRoot, &bestSubtree, &bestGraftNode1,
                       &bestGraftNode2, config);
        graftRecursive(tree, i + tree->leaves, edge2, edge3, edge1, &bestScore,
                       &bestPruneRoot, &bestSubtree, &bestGraftNode1,
                       &bestGraftNode2, config);
        subtreeRegraft(tree, i + tree->leaves, edge1, edge3);
      }

      // Prune and regraft edge3
      if (!isLeaf(tree, edge2) || !isLeaf(tree, edge3)) {
        subtreePrune(tree, i + tree->leaves, edge3);
        graftRecursive(tree, i + tree->leaves, edge3, edge1, edge2, &bestScore,
                       &bestPruneRoot, &bestSubtree, &bestGraftNode1,
                       &bestGraftNode2, config);
        graftRecursive(tree, i + tree->leaves, edge3, edge2, edge1, &bestScore,
                       &bestPruneRoot, &bestSubtree, &bestGraftNode1,
                       &bestGraftNode2, config);
        subtreeRegraft(tree, i + tree->leaves, edge1, edge2);
      }

      if (bestPruneRoot >= 0) {
        subtreePrune(tree, bestPruneRoot, bestSubtree);
        subtreeRegraft(tree, bestPruneRoot, bestGraftNode1, bestGraftNode2);
      }
    }

  } while (bestScore < score);
}

// Single replicate of hill climbing search returning one optimal tree
tree_t *hillClimbingReplicate(alignment_t *alignment, config_t *config) {
  // Initialize a random tree
  tree_t *tree = randomTree(alignment);
  int score = config->evalFn(tree, config);

#ifdef DEBUG
  printf("Starting with tree:\n");
  printTree(tree);
  printNewick(tree, stdout);
  printf(";\n");
#endif /* ifdef DEBUG */

  switch (config->hc_operator) {
  case NNI:
    nniCicle(tree, score, config);
    break;
  case SPR:
    sprCicle(tree, score, config);
    break;
  }

  return tree;
}

// Perform a search using a hill climbing optimization algorithm
answer_t *hillClimbingSearch(alignment_t *alignment, config_t *config) {
  answer_t *answer = initializeAnswer(config->answer_size);

  for (int i = 0; i < config->hc_replicates; i++) {
#ifdef DEBUG
    printf("-- HC Replicate %d --\n", i + 1);
#endif /* ifdef DEBUG */
    tree_t *tree = hillClimbingReplicate(alignment, config);
    updateAnswer(answer, tree, config->evalFn(tree, config));
    destroyTree(tree);
  }

  return answer;
}
