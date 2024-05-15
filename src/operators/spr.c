#include "spr.h"

#include <stdio.h>
#include <tree/random.h>
#include <tree/tree.h>

// Determine node to the "left" of subtree
int findLeft(tree_t *tree, int pruneNode, int pruneEdge) {
  if (pruneEdge == tree->nodes[pruneNode].edge1)
    return tree->nodes[pruneNode].edge2;
  return tree->nodes[pruneNode].edge1;
}

// Determine node to the "right" of subtree
int findRight(tree_t *tree, int pruneNode, int pruneEdge) {
  if (pruneEdge == tree->nodes[pruneNode].edge3)
    return tree->nodes[pruneNode].edge2;
  return tree->nodes[pruneNode].edge3;
}

// Performs the pruning step of SPR, separating the subtree rooted in pruneRoot.
// Returns a "root" to the leftover tree.
int subtreePrune(tree_t *tree, int pruneRoot, int subtree) {
  if (!tree || pruneRoot < 0 || isLeaf(tree, pruneRoot))
    return tree->root;

  int leftNode = findLeft(tree, pruneRoot, subtree);
  int rightNode = findRight(tree, pruneRoot, subtree);

  changeEdge(tree, leftNode, pruneRoot, rightNode);
  changeEdge(tree, rightNode, pruneRoot, leftNode);
  changeEdge(tree, pruneRoot, leftNode, -1);
  changeEdge(tree, pruneRoot, rightNode, -1);

  if (isLeaf(tree, leftNode))
    return rightNode;
  return leftNode;
}

// Performs the grafting step of SPR, attaching pruneRoot to the edge defined by
// graftNode1 and graftNode2.
void subtreeRegraft(tree_t *tree, int pruneRoot, int graftNode1,
                    int graftNode2) {
  if (!tree || pruneRoot < 0)
    return;

  changeEdge(tree, graftNode1, graftNode2, pruneRoot);
  changeEdge(tree, graftNode2, graftNode1, pruneRoot);
  changeEdge(tree, pruneRoot, -1, graftNode1);
  changeEdge(tree, pruneRoot, -1, graftNode2);
}

// Performs a random SPR operation on the tree.
void randomSPR(tree_t *tree) {
  // Select a random internal node to be the cut point
  int pruneRoot = randomInternalNode(tree->leaves);

  // Select a random edge from the root to be the pruned subtree
  int subtree = randomEdge(tree, pruneRoot);

#ifdef DEBUG
  printf("Pruning subtree (%d %d)\n", pruneRoot, subtree);
#endif /* ifdef DEBUG */

  // Prune subtree and get a starting place in remaining subtree
  int remainingTree = subtreePrune(tree, pruneRoot, subtree);

  // Select a random edge to graft
  int graftNode1, graftNode2;
  randomSubtree(tree, remainingTree, &graftNode1, &graftNode2, 0.5);

#ifdef DEBUG
  printf("Regrafting at (%d %d)\n", graftNode1, graftNode2);
#endif /* ifdef DEBUG */

  // Graft subtree into new edge
  subtreeRegraft(tree, pruneRoot, graftNode1, graftNode2);
}
