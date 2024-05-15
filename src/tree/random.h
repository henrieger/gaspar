#ifndef __TREE_RANDOM_H__
#define __TREE_RANDOM_H__

#include "tree.h"
#include <sequence-alignment/sequence-alignment.h>

// Generate a random unrooted binrary tree from alignment.
tree_t *randomTree(alignment_t *alignment);

// Return a random node on the tree.
int randomNode(int numLeaves);

#endif // !__TREE_RANDOM_H__
