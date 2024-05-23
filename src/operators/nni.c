#include "nni.h"

#include <sequence-alignment/sequence-alignment.h>
#include <stdio.h>
#include <stdlib.h>
#include <tree/random.h>
#include <tree/tree.h>
#include <config.h>

// Find the node in n1 to be swapped
int findN1Swapper(tree_t *tree, int n1, int n2) {
  if (tree->nodes[n1].edge3 == n2)
    return tree->nodes[n1].edge2;
  return tree->nodes[n1].edge3;
}

// Find the node in n2 to be swapped
int findN2Swapper(tree_t *tree, int n1, int n2, int joint) {
  if (joint == 1 && tree->nodes[n2].edge1 != n1)
    return tree->nodes[n2].edge1;
  if (tree->nodes[n2].edge3 != n1)
    return tree->nodes[n2].edge3;
  return tree->nodes[n2].edge2;
}

// Create a Nearest Neighbor Interchange operation in the out edge connected to
// node. Select the new joint by integer index (2 possible). Assumes unrooted
// binary tree. Leaves not accepted as input.
void nni(tree_t *tree, int n1, int n2, int joint) {
  int n1Swapper = findN1Swapper(tree, n1, n2);
  int n2Swapper = findN2Swapper(tree, n1, n2, joint);

  changeEdge(tree, n1, n1Swapper, n2Swapper);
  changeEdge(tree, n2, n2Swapper, n1Swapper);
  changeEdge(tree, n1Swapper, n1, n2);
  changeEdge(tree, n2Swapper, n2, n1);
}

// Do a random NNI operation on the tree
void randomNNI(tree_t *tree, config_t *config) {
  // Select the index of a random internal node
  int n1 = randomInternalNode(tree->leaves);

  // Select the edge in which the NNI will occur
  int n2 = randomInternalEdge(tree, n1);

  // Select the joint for the NNi
  int joint = rand() % 2;

  nni(tree, n1, n2, joint);
}
