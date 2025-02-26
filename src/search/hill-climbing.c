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
  nni(tree, n1, n2, joint);
  int score = config->evalFn(tree, config);

#ifdef DEBUG
  printf("NNI between %d and %d (joint %d) - Score %d\n", n1, n2, joint, score);
#endif /* ifdef DEBUG */

  if (score < *bestScore) {
    *bestScore = score;
    *bestN1 = n1;
    *bestN2 = n2;
    *bestJoint = joint;
  }
  nni(tree, n1, n2, joint);
}

int wasEvaluated(int *evaluated, int size, int leaf) {
  for (int i = 0; i < size; i++) {
    if (evaluated[i] == leaf)
      return 1;
  }
  return 0;
}

void nniCicle(tree_t *tree, int score, config_t *config, answer_t *answer) {
  int bestScore = score;
  int bestN1 = -1;
  int bestN2 = -1;
  int bestJoint = -1;

  int internalNodes = tree->leaves - 2;
  int *evaluated = malloc(internalNodes * sizeof(int));

  do {
    score = bestScore;
    bestN1 = -1;

#ifdef DEBUG
    printf("Best score: %d\n", score);
#endif /* ifdef DEBUG */

    for (int i = 0; i < internalNodes; i++)
      evaluated[i] = -1;

    for (int i = 0; i < internalNodes; i++) {
      if (tree->internal[i].edges[0] >= tree->leaves &&
          !wasEvaluated(evaluated, internalNodes, tree->internal[i].edges[0])) {
        evaluateNNI(tree, config, tree->leaves + i, tree->internal[i].edges[0],
                    0, &bestN1, &bestN2, &bestJoint, &bestScore);
        evaluateNNI(tree, config, tree->leaves + i, tree->internal[i].edges[0],
                    1, &bestN1, &bestN2, &bestJoint, &bestScore);
      }
      if (tree->internal[i].edges[1] >= tree->leaves &&
          !wasEvaluated(evaluated, internalNodes, tree->internal[i].edges[1])) {
        evaluateNNI(tree, config, tree->leaves + i, tree->internal[i].edges[1],
                    0, &bestN1, &bestN2, &bestJoint, &bestScore);
        evaluateNNI(tree, config, tree->leaves + i, tree->internal[i].edges[1],
                    1, &bestN1, &bestN2, &bestJoint, &bestScore);
      }
      if (tree->internal[i].edges[2] >= tree->leaves &&
          !wasEvaluated(evaluated, internalNodes, tree->internal[i].edges[2])) {
        evaluateNNI(tree, config, tree->leaves + i, tree->internal[i].edges[2],
                    0, &bestN1, &bestN2, &bestJoint, &bestScore);
        evaluateNNI(tree, config, tree->leaves + i, tree->internal[i].edges[2],
                    1, &bestN1, &bestN2, &bestJoint, &bestScore);
      }

      evaluated[i] = tree->leaves + i;
    }

    if (bestN1 >= 0) {
      nni(tree, bestN1, bestN2, bestJoint);
      updateAnswer(answer, tree, bestScore);
    }

  } while (bestScore < score);

  free(evaluated);
}

void graftRecursive(tree_t *tree, int pruneRoot, int subtree, int left,
                    int right, int *bestScore, int *bestPruneRoot,
                    int *bestSubtree, int *bestGraftNode1, int *bestGraftNode2,
                    config_t *config) {
  int edges[3];
  edges[0] = tree->nodes[right].edges[0];
  edges[1] = tree->nodes[right].edges[1];
  edges[2] = tree->nodes[right].edges[2];

  if (edges[0] > 0 && edges[0] != left) {
    subtreeRegraft(tree, pruneRoot, right, edges[0]);
    int score = config->evalFn(tree, config);

#ifdef DEBUG
    printf("\tGrafting onto %d - %d: Score %d\n", right, edges[0], score);
#endif /* ifdef DEBUG */

    if (score < *bestScore) {
      *bestScore = score;
      *bestPruneRoot = pruneRoot;
      *bestSubtree = subtree;
      *bestGraftNode1 = right;
      *bestGraftNode2 = edges[0];
    }
    subtreePrune(tree, pruneRoot, subtree);
    graftRecursive(tree, pruneRoot, subtree, right, edges[0], bestScore,
                   bestPruneRoot, bestSubtree, bestGraftNode1, bestGraftNode2,
                   config);
  }
  if (edges[1] > 0 && edges[1] != left) {
    subtreeRegraft(tree, pruneRoot, right, edges[1]);
    int score = config->evalFn(tree, config);

#ifdef DEBUG
    printf("\tGrafting onto %d - %d: Score %d\n", right, edges[1], score);
#endif /* ifdef DEBUG */

    if (score < *bestScore) {
      *bestScore = score;
      *bestPruneRoot = pruneRoot;
      *bestSubtree = subtree;
      *bestGraftNode1 = right;
      *bestGraftNode2 = edges[1];
    }
    subtreePrune(tree, pruneRoot, subtree);
    graftRecursive(tree, pruneRoot, subtree, right, edges[1], bestScore,
                   bestPruneRoot, bestSubtree, bestGraftNode1, bestGraftNode2,
                   config);
  }
  if (edges[2] > 0 && edges[2] != left) {
    subtreeRegraft(tree, pruneRoot, right, edges[2]);
    int score = config->evalFn(tree, config);

#ifdef DEBUG
    printf("\tGrafting onto %d - %d: Score %d\n", right, edges[2], score);
#endif /* ifdef DEBUG */

    if (score < *bestScore) {
      *bestScore = score;
      *bestPruneRoot = pruneRoot;
      *bestSubtree = subtree;
      *bestGraftNode1 = right;
      *bestGraftNode2 = edges[2];
    }
    subtreePrune(tree, pruneRoot, subtree);
    graftRecursive(tree, pruneRoot, subtree, right, edges[2], bestScore,
                   bestPruneRoot, bestSubtree, bestGraftNode1, bestGraftNode2,
                   config);
  }
}

void sprCicle(tree_t *tree, int score, config_t *config, answer_t *answer) {
  int bestScore = score;
  int bestPruneRoot = -1;
  int bestSubtree = -1;
  int bestGraftNode1 = -1;
  int bestGraftNode2 = -1;

  int internalNodes = tree->leaves - 2;
  int pruneRoot;
  int edges[3];

  do {
    score = bestScore;

    for (int i = 0; i < internalNodes; i++) {
      pruneRoot = i + tree->leaves;
      edges[0] = tree->internal[i].edges[0];
      edges[1] = tree->internal[i].edges[1];
      edges[2] = tree->internal[i].edges[2];

      // Prune and regraft edges[0]
      if (!isLeaf(tree, edges[1]) || !isLeaf(tree, edges[2])) {
#ifdef DEBUG
        printf("Pruning subtree %d - %d\n", pruneRoot, edges[0]);
#endif /* ifdef DEBUG */
        subtreePrune(tree, pruneRoot, edges[0]);
        graftRecursive(tree, pruneRoot, edges[0], edges[1], edges[2],
                       &bestScore, &bestPruneRoot, &bestSubtree,
                       &bestGraftNode1, &bestGraftNode2, config);
        graftRecursive(tree, pruneRoot, edges[0], edges[2], edges[1],
                       &bestScore, &bestPruneRoot, &bestSubtree,
                       &bestGraftNode1, &bestGraftNode2, config);
        subtreeRegraft(tree, pruneRoot, edges[1], edges[2]);
      }

      // Prune and regraft edges[1]
      if (!isLeaf(tree, edges[0]) || !isLeaf(tree, edges[2])) {
#ifdef DEBUG
        printf("Pruning subtree %d - %d\n", pruneRoot, edges[1]);
#endif /* ifdef DEBUG */
        subtreePrune(tree, pruneRoot, edges[1]);
        graftRecursive(tree, pruneRoot, edges[1], edges[0], edges[2],
                       &bestScore, &bestPruneRoot, &bestSubtree,
                       &bestGraftNode1, &bestGraftNode2, config);
        graftRecursive(tree, pruneRoot, edges[1], edges[2], edges[0],
                       &bestScore, &bestPruneRoot, &bestSubtree,
                       &bestGraftNode1, &bestGraftNode2, config);
        subtreeRegraft(tree, pruneRoot, edges[0], edges[2]);
      }

      // Prune and regraft edges[2]
      if (!isLeaf(tree, edges[0]) || !isLeaf(tree, edges[1])) {
#ifdef DEBUG
        printf("Pruning subtree %d - %d\n", pruneRoot, edges[2]);
#endif /* ifdef DEBUG */
        subtreePrune(tree, pruneRoot, edges[2]);
        graftRecursive(tree, pruneRoot, edges[2], edges[0], edges[1],
                       &bestScore, &bestPruneRoot, &bestSubtree,
                       &bestGraftNode1, &bestGraftNode2, config);
        graftRecursive(tree, pruneRoot, edges[2], edges[1], edges[0],
                       &bestScore, &bestPruneRoot, &bestSubtree,
                       &bestGraftNode1, &bestGraftNode2, config);
        subtreeRegraft(tree, pruneRoot, edges[0], edges[1]);
      }
    }

    if (bestPruneRoot >= 0) {
      subtreePrune(tree, bestPruneRoot, bestSubtree);
      subtreeRegraft(tree, bestPruneRoot, bestGraftNode1, bestGraftNode2);
      updateAnswer(answer, tree, bestScore);
    }

#ifdef DEBUG
    printf("New tree: ");
    printNewick(tree, stdout);
    printf(" - Score %d\n", bestScore);
#endif /* ifdef DEBUG */
  } while (bestScore < score);
}

// Single replicate of hill climbing search returning one optimal tree
tree_t *hillClimbingReplicate(alignment_t *alignment, config_t *config,
                              answer_t *answer) {
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
    nniCicle(tree, score, config, answer);
    break;
  case SPR:
    sprCicle(tree, score, config, answer);
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
    tree_t *tree = hillClimbingReplicate(alignment, config, answer);
    destroyTree(tree);
  }

  return answer;
}
