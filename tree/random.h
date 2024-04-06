#ifndef __TREE_RANDOM_H__
#define __TREE_RANDOM_H__

#include "tree.h"
#include <sequence-alignment/sequence-alignment.h>

// Generate a random unrooted binrary tree from alignment
tree_t *randomUnrootedBinaryTree(alignment_t alignment,
                                 alignment_t auxAlignment);

#endif // !__TREE_RANDOM_H__
