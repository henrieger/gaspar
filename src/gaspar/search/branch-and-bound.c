#include <gaspar/search/branch-and-bound.h>

#include <gaspar/answer/answer.h>
#include <gaspar/base/config.h>
#include <gaspar/sequence-alignment/sequence-alignment.h>
#include <gaspar/tree/iterator.h>
#include <gaspar/tree/tree.h>

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

// Recursive branch and bound search, keeping track of origin of call.
void branchAndBoundRecursive(tree_t *tree, config_t *config, uint32_t taxon,
                             answer_t *answer) {
  int score = config->evalFn(tree, config);
  if (score > getScore(answer))
    return;

  if (taxon >= tree->alignment->taxa) {
    updateAnswer(answer, tree, score);
    return;
  }

  treeIterator_t *it = newSubtreeIterator(tree, tree->right[0]);

  uint32_t internalNode = taxon - 1;
  uint32_t leafNode = treeInternalNodes(tree) + taxon;
  tree->parent[leafNode] = internalNode;
  tree->left[internalNode] = leafNode;

  for (int32_t node = nextTreeIterator(it); node != NULL_EDGE;
       node = nextTreeIterator(it)) {
    int32_t nodeParent = tree->parent[node];
    bool nodeToLeft = tree->left[nodeParent] == node;
    if (nodeToLeft) {
      tree->left[nodeParent] = internalNode;
    } else {
      tree->right[nodeParent] = internalNode;
    }

    tree->parent[node] = internalNode;
    tree->parent[internalNode] = nodeParent;
    tree->right[internalNode] = node;
    branchAndBoundRecursive(tree, config, taxon + 1, answer);

    tree->parent[node] = nodeParent;
    tree->parent[internalNode] = NULL_EDGE;
    if (nodeToLeft) {
      tree->left[nodeParent] = node;
    } else {
      tree->right[nodeParent] = node;
    }
  }

  destroyIterator(it);
}

// Performs a branch and bound search with given alignment and eval function.
answer_t *branchAndBoundSearch(alignment_t *alignment, config_t *config) {
  if (alignment->taxa < 3)
    return NULL;

  answer_t *answer = initializeAnswer(config->answer_size, alignment);

  tree_t *tree = newTree(alignment);
  smallestTree(tree);
  branchAndBoundRecursive(tree, config, 3, answer);

  destroyTree(tree);
  return answer;
}
