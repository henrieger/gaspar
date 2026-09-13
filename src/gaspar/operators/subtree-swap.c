#include <gaspar/operators/subtree-swap.h>

#include <gaspar/base/config.h>
#include <gaspar/tree/random.h>
#include <gaspar/tree/tree.h>

#include <stdbool.h>
#include <stdint.h>

void subtreeSwap(tree_t *tree, uint32_t n1, uint32_t n2) {
  int32_t n1Parent = tree->parent[n1];
  int32_t n2Parent = tree->parent[n2];

  bool n1ToLeft = tree->left[n1Parent] == n1;
  bool n2ToLeft = tree->left[n2Parent] == n2;

  if (n1ToLeft) {
    tree->left[n1Parent] = n2;
  } else {
    tree->right[n1Parent] = n2;
  }

  if (n2ToLeft) {
    tree->left[n2Parent] = n1;
  } else {
    tree->right[n2Parent] = n1;
  }

  tree->parent[n1] = n2Parent;
  tree->parent[n2] = n1Parent;
}

void randomSubtreeSwap(tree_t *tree, config_t *config) {
  uint32_t n1 = 0;
  while (n1 == 0 || n1 == tree->left[0] || n1 == tree->right[0]) {
    n1 = randomNode(tree);
  }

  uint32_t n2 = 0;
  while (n2 == 0 || n2 == tree->left[0] || n2 == tree->right[0] ||
         isAncestor(tree, n1, n2) || isAncestor(tree, n2, n1)) {
    n2 = randomNode(tree);
  }

  subtreeSwap(tree, n1, n2);
}
