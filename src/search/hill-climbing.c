#include "hill-climbing.h"

#include <answer/answer.h>
#include <config.h>
#include <math.h>
#include <operators/nni.h>
#include <operators/spr.h>
#include <operators/subtree-swap.h>
#include <sequence-alignment/sequence-alignment.h>
#include <stdint.h>
#include <tree/iterator.h>
#include <tree/random.h>
#include <tree/tree.h>

struct bestNNI {
  uint32_t n1, n2, joint;
};

struct bestSPR {
  uint32_t p1, p2, g1, g2;
};

struct bestSubtreeSwap {
  uint32_t n1, n2;
};

union bestMove {
  struct bestNNI NNI;
  struct bestSPR SPR;
  struct bestSubtreeSwap subtreeSwap;
};

struct bestGraft {
  uint32_t g1, g2;
  double score;
};

double nniLocalSearch(tree_t *tree, config_t *config, struct bestNNI *best) {
  best->n1 = NULL_EDGE;
  best->n2 = NULL_EDGE;
  best->joint = 0;

  double bestLocalScore = INFINITY;
  treeIterator_t *it = newSubtreeIterator(tree, tree->right[0]);

  nextTreeIterator(it);
  for (int32_t n2 = nextTreeIterator(it); n2 != NULL_EDGE;
       n2 = nextTreeIterator(it)) {
    if (n2 >= treeLeaves(tree))
      continue;

    double treeScore;
    uint32_t n1 = tree->parent[n2];

    nni(tree, n1, n2, 0);
    treeScore = config->evalFn(tree, config);
    if (treeScore < bestLocalScore) {
      bestLocalScore = treeScore;
      best->n1 = n1;
      best->n2 = n2;
      best->joint = 0;
    }
    nni(tree, n1, n2, 0);

    nni(tree, n1, n2, 1);
    treeScore = config->evalFn(tree, config);
    if (treeScore < bestLocalScore) {
      bestLocalScore = treeScore;
      best->n1 = n1;
      best->n2 = n2;
      best->joint = 1;
    }
    nni(tree, n1, n2, 1);
  }

  destroyIterator(it);
  return bestLocalScore;
}

struct bestGraft graftIterative(tree_t *tree, config_t *config, uint32_t p1,
                                uint32_t p2, struct bestSPR *best) {
  struct bestGraft bestGraft = {.score = INFINITY};

  treeIterator_t *it = newSubtreeIterator(tree, tree->right[0]);

  for (int32_t g2 = nextTreeIterator(it); g2 != NULL_EDGE;
       g2 = nextTreeIterator(it)) {
    int32_t g1 = tree->parent[g2];
    subtreeGraft(tree, p1, p2, g1, g2);
    double score = config->evalFn(tree, config);
    if (score < bestGraft.score) {
      bestGraft.score = score;
      bestGraft.g1 = g1;
      bestGraft.g2 = g2;
    }

    subtreePrune(tree, p1, p2);
  }

  destroyIterator(it);
  return bestGraft;
}

double sprLocalSearch(tree_t *tree, config_t *config, struct bestSPR *best) {
  best->p1 = best->p2 = best->g1 = best->g2 = NULL_EDGE;

  double bestLocalScore = INFINITY;
  treeIterator_t *it = newSubtreeIterator(tree, tree->right[0]);
  uint32_t p1, p2, oldG1, oldG2;

  nextTreeIterator(it);
  for (p2 = nextTreeIterator(it); p2 != NULL_EDGE; p2 = nextTreeIterator(it)) {
    p1 = tree->parent[p2];

    oldG1 = tree->parent[p1];
    if (tree->left[p1] == p2) {
      oldG2 = tree->right[p1];
    } else {
      oldG2 = tree->left[p1];
    }

    subtreePrune(tree, p1, p2);
    struct bestGraft bestGraft = graftIterative(tree, config, p1, p2, best);
    if (bestGraft.score < bestLocalScore) {
      bestLocalScore = bestGraft.score;
      best->p1 = p1;
      best->p2 = p2;
      best->g1 = bestGraft.g1;
      best->g2 = bestGraft.g2;
    }
    subtreeGraft(tree, p1, p2, oldG1, oldG2);
  }

  destroyIterator(it);
  return bestLocalScore;
}

double subtreeSwapLocalSearch(tree_t *tree, config_t *config,
                              struct bestSubtreeSwap *best) {
  best->n1 = NULL_EDGE;
  best->n2 = NULL_EDGE;
  double bestLocalScore = INFINITY;

  treeIterator_t *externalIt = newSubtreeIterator(tree, tree->right[0]);
  treeIterator_t *internalIt = newSubtreeIterator(tree, tree->right[0]);

  nextTreeIterator(externalIt);
  for (int32_t n1 = nextTreeIterator(externalIt); n1 != NULL_EDGE;
       n1 = nextTreeIterator(externalIt)) {
    resetTreeIterator(internalIt);

    nextTreeIterator(internalIt);
    for (int32_t n2 = nextTreeIterator(internalIt); n2 != NULL_EDGE;
         n2 = nextTreeIterator(internalIt)) {
      if (isAncestor(tree, n1, n2) || isAncestor(tree, n2, n1)) {
        continue;
      }

      subtreeSwap(tree, n1, n2);
      double treeScore = config->evalFn(tree, config);
      if (treeScore < bestLocalScore) {
        best->n1 = n1;
        best->n2 = n2;
        bestLocalScore = treeScore;
      }
      subtreeSwap(tree, n1, n2);
    }
  }

  destroyIterator(externalIt);
  destroyIterator(internalIt);

  return bestLocalScore;
}

// Choose adequate search loop based on the defined operator
double localSearch(tree_t *tree, config_t *config, union bestMove *bestMove) {
#ifdef DEBUG
  printf("Starting with tree:\n");
  printTree(tree);
#endif /* ifdef DEBUG */

  double score = 0;
  switch (config->hc_operator) {
  case NNI:
    score = nniLocalSearch(tree, config, &bestMove->NNI);
    break;
  case SPR:
    score = sprLocalSearch(tree, config, &bestMove->SPR);
    break;
  case SUBTREE_SWAP:
    score = subtreeSwapLocalSearch(tree, config, &bestMove->subtreeSwap);
    break;
  }
  return score;
}

// Perform the best move found by local search, depending on operator
void makeBestMove(tree_t *tree, config_t *config, union bestMove bestMove) {
  switch (config->hc_operator) {
  case NNI:
    nni(tree, bestMove.NNI.n1, bestMove.NNI.n2, bestMove.NNI.joint);
    break;
  case SPR:
    subtreePrune(tree, bestMove.SPR.p1, bestMove.SPR.p2);
    subtreeGraft(tree, bestMove.SPR.p1, bestMove.SPR.p2, bestMove.SPR.g1,
                 bestMove.SPR.g2);
    break;
  case SUBTREE_SWAP:
    subtreeSwap(tree, bestMove.subtreeSwap.n1, bestMove.subtreeSwap.n2);
    break;
  }
}

// Perform a search using a hill climbing optimization algorithm
answer_t *hillClimbingSearch(alignment_t *alignment, config_t *config) {
  answer_t *answer = initializeAnswer(config->answer_size, alignment);
  tree_t *tree = newTree(alignment);
  union bestMove bestMove;

  for (int replicate = 0; replicate < config->hc_replicates; replicate++) {
#ifdef DEBUG
    printf("-- HC Replicate %d --\n", replicate + 1);
#endif /* ifdef DEBUG */

    // Initialize a random tree
    randomTree(tree);

#ifdef DEBUG
    int round = 1;
#endif /* ifdef DEBUG */
    for (double score = localSearch(tree, config, &bestMove);
         score < getScore(answer);
         score = localSearch(tree, config, &bestMove)) {

#ifdef DEBUG
      printf("Search round %d\n", round);
#endif /* ifdef DEBUG */

      makeBestMove(tree, config, bestMove);
      updateAnswer(answer, tree, score);
#ifdef DEBUG
      round++;
#endif /* ifdef DEBUG */
    }
  }

  destroyTree(tree);
  return answer;
}
