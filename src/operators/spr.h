#ifndef __SPR_H__

#include <tree/tree.h>

// Performs the pruning step of SPR, separating a subtree rooted in pruneRoot.
// Returns a "root" to the leftover tree.
int subtreePrune(tree_t *tree, int pruneRoot, int subtree);

// Performs the grafting step of SPR, attaching pruneRoot to the edge defined by
// graftNode1 and graftNode2.
void subtreeRegraft(tree_t *tree, int pruneRoot, int graftNode1,
                    int graftNode2);

// Performs a random SPR operation on the tree.
void randomSPR(tree_t *tree);

#endif // !__SPR_H__
