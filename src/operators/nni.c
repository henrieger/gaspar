#include "nni.h"

#include <config.h>
#include <sequence-alignment/sequence-alignment.h>
#include <stdint.h>
#include <stdlib.h>
#include <tree/random.h>
#include <tree/tree.h>

// Create a Nearest Neighbor Interchange operation in the out edge connected to
// node. Select the new joint by integer index (2 possible). Assumes unrooted
// binary tree. Leaves not accepted as input.
void nni(tree_t *tree, int32_t n1, int32_t n2, int joint) {
  // If direction is from leaf to root, call with parameters inverted
  if (tree->parent[n1] == n2)
    return nni(tree, n2, n1, joint);

  // Determine if n2 is at the left or right of n1
  // so that the correct node is interchanged
  int32_t n1InterchangedNode = tree->left[n1];
  if (tree->left[n1] == n2) {
    n1InterchangedNode = tree->right[n1];
  }

  // Determine which child node of n2 to interchange
  int32_t n2InterchangedNode = tree->left[n2];
  if (joint)
    n2InterchangedNode = tree->right[n2];

  // Do the interchange
  tree->parent[n1InterchangedNode] = n2;
  tree->parent[n2InterchangedNode] = n1;
  if (tree->left[n1] == n2)
    tree->right[n1] = n2InterchangedNode;
  else
    tree->left[n1] = n2InterchangedNode;
  if (joint)
    tree->right[n2] = n1InterchangedNode;
  else
    tree->left[n2] = n1InterchangedNode;
}

// Do a random NNI operation on the tree
void randomNNI(tree_t *tree, config_t *config) {
  // Select the index of a random internal node
  uint32_t n2 = 0, n1 = 0;
  while (n2 == 0 || n1 == 0) {
    n2 = randomInternalNode(tree);
    n1 = tree->parent[n2];
  }

  // Select the joint for the NNi
  int joint = rand() % 2;

  nni(tree, n1, n2, joint);
}
