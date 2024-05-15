#ifndef __TREE_RANDOM_H__
#define __TREE_RANDOM_H__

#include "tree.h"
#include <sequence-alignment/sequence-alignment.h>

// Generate a random unrooted binrary tree from alignment.
tree_t *randomTree(alignment_t *alignment);

// Return a random node index on the tree.
int randomNode(int size);

// Return a random internal node index on the tree
int randomInternalNode(int numLeaves);

// Return a random non-null edge of node
int randomEdge(tree_t *tree, int node);

// Return a random internal edge of node
int randomInternalEdge(tree_t *tree, int node);

// Return the edge of a random subtree from the given edge
void randomSubtree(tree_t *tree, int node, int *subtree1, int *subtree2,
                   double probability);

#endif // !__TREE_RANDOM_H__
