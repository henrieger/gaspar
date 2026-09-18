#ifndef __LIBGASPAR_OPERATORS_H__
#define __LIBGASPAR_OPERATORS_H__

#include <gaspar/config.h>
#include <gaspar/tree.h>

#include <stdint.h>

// Create a Nearest Neighbor Interchange operation in the out edge connected to
// node. Select the new joint by integer index (2 possible). Assumes unrooted
// binary tree. Leaves not accepted as input.
void nni(tree_t *tree, int32_t n1, int32_t n2, int joint);

// Do a random NNI operation on the tree
void randomNNI(tree_t *tree, config_t *config);

// Prune subtree rooted in (p1, p2).
void subtreePrune(tree_t *tree, uint32_t p1, uint32_t p2);

// Graft subtree rooted in (p1, p2) to edge (g1, g2).
void subtreeGraft(tree_t *tree, uint32_t p1, uint32_t p2, uint32_t g1,
                  uint32_t g2);

// Performs a random SPR operation on the tree.
void randomSPR(tree_t *tree, config_t *config);

void subtreeSwap(tree_t *tree, uint32_t n1, uint32_t n2);

void randomSubtreeSwap(tree_t *tree, config_t *config);

// Random NNI or SPR
void hybridOp(tree_t *tree, config_t *config);

#endif // !__LIBGASPAR_OPERATORS_H__
