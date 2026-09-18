#include "correct-tree.h"

#include <gaspar/tree/tree.h>

#include <assert.h>

// Check if tree has expected format (Alpha((Beta,Epsilon),(Gamma,Delta))); or
// similar
void assertTreeCorrectness(tree_t *tree) {
  // Check that Alpha is left of root
  assert(tree->left[0] == 4);

  // Beta is sister to Epsilon
  assert(isSisterNode(tree, 5, 8));

  // Gamma is sister to Delta
  assert(isSisterNode(tree, 6, 7));

  // (Beta,Epsilon) is sister to (Gamma,Delta)
  uint32_t betaEpsilon = tree->parent[5];
  uint32_t gammaDelta = tree->parent[6];
  assert(isSisterNode(tree, betaEpsilon, gammaDelta));

  // Alpha is sister to all
  uint32_t allExceptAlpha = tree->parent[betaEpsilon];
  assert(tree->right[0] == allExceptAlpha);
  assert(isSisterNode(tree, 4, allExceptAlpha));
}
