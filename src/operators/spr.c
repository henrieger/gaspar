#include "spr.h"
#include "tree/iterator.h"

#include <config.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <tree/random.h>
#include <tree/tree.h>

void subtreePrune(tree_t *tree, uint32_t p1, uint32_t p2) {
  // Find out whether p1 is at the left or right of its parent
  uint32_t p1Parent = tree->parent[p1];
  bool p1ToLeft = tree->left[p1Parent] == p1;

  // Find out whether p2 is at the left or right of p1
  bool p2ToLeft = tree->left[p1] == p2;

  // Cut the subtree at p2 and then erase p1 from the tree
  if (p1ToLeft && p2ToLeft) {
    tree->left[p1Parent] = tree->right[p1];
    tree->parent[tree->right[p1]] = p1Parent;
  } else if (p1ToLeft && !p2ToLeft) {
    tree->left[p1Parent] = tree->left[p1];
    tree->parent[tree->left[p1]] = p1Parent;
  } else if (!p1ToLeft && p2ToLeft) {
    tree->right[p1Parent] = tree->right[p1];
    tree->parent[tree->right[p1]] = p1Parent;
  } else {
    tree->right[p1Parent] = tree->left[p1];
    tree->parent[tree->left[p1]] = p1Parent;
  }
}

void subtreeGraft(tree_t *tree, uint32_t p1, uint32_t p2, uint32_t g1,
                  uint32_t g2) {
  // Find out whether p2 is at the left or right of p1
  bool p2ToLeft = tree->left[p1] == p2;

  // Find out whether p2 is at the left or right of p1
  bool g2ToLeft = tree->left[g1] == g2;

  // Put p1 in between g1 and g2
  tree->parent[p1] = g1;
  tree->parent[g2] = p1;
  if (p2ToLeft && g2ToLeft) {
    tree->left[g1] = p1;
    tree->right[p1] = g2;
  } else if (p2ToLeft && !g2ToLeft) {
    tree->right[g1] = p1;
    tree->right[p1] = g2;
  } else if (!p2ToLeft && g2ToLeft) {
    tree->left[g1] = p1;
    tree->left[p1] = g2;
  } else {
    tree->right[g1] = p1;
    tree->left[p1] = g2;
  }
}

// Performs a random SPR operation on the tree.
void randomSPR(tree_t *tree, config_t *config) {
  // Select a random pruning edge
  int32_t p1 = 0, p2 = 0;
  while (p1 == 0 || p2 == 0) {
    p2 = randomInternalNode(tree);
    p1 = tree->parent[p2];
  }

  // Prune subtree and guarantee an iterable base tree
  subtreePrune(tree, p1, p2);

  // Travel base tree and select a random node for grafting
  treeIterator *it = newTreeIterator(tree);
  for (uint32_t g2 = nextTreeIterator(it); g2 != NULL_EDGE;
       g2 = nextTreeIterator(it)) {
    if (g2 == 0 || g2 == firstLeaf(tree))
      continue;

    if ((double)rand() / (double)RAND_MAX < config->spr_probability) {
      int32_t g1 = tree->parent[g2];
      subtreeGraft(tree, p1, p2, g1, g2);
      destroyIterator(it);
      return;
    }
  }

  // If didn't find a regraft point, regraft at root (for simplicity, for now)
  subtreeGraft(tree, p1, p2, 0, tree->right[0]);
  destroyIterator(it);
}
