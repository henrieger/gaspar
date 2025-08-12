#ifndef __TREE_RANDOM_H__
#define __TREE_RANDOM_H__

#include "tree.h"
#include <sequence-alignment/sequence-alignment.h>
#include <stdint.h>

// Generate a random unrooted binrary tree from alignment.
void randomTree(tree_t *tree);

// Return a random node index on the tree.
uint32_t randomNode(tree_t *tree);

// Return a random internal node index on the tree
uint32_t randomInternalNode(tree_t *tree);

// Return a random non-null edge of node
uint32_t randomEdge(tree_t *tree, int node);

// Return a random internal edge of node
uint32_t randomInternalEdge(tree_t *tree, uint32_t node);

// Return the edge of a random subtree from the given edge
void randomSubtree(tree_t *tree, int node, int *subtree1, int *subtree2,
                   double probability);

#endif // !__TREE_RANDOM_H__
