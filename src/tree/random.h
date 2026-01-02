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

#endif // !__TREE_RANDOM_H__
