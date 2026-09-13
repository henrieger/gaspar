#ifndef __SPR_H__

#include <gaspar/base/config.h>
#include <gaspar/tree/tree.h>

// Prune subtree rooted in (p1, p2).
void subtreePrune(tree_t *tree, uint32_t p1, uint32_t p2);

// Graft subtree rooted in (p1, p2) to edge (g1, g2).
void subtreeGraft(tree_t *tree, uint32_t p1, uint32_t p2, uint32_t g1,
                  uint32_t g2);

// Performs a random SPR operation on the tree.
void randomSPR(tree_t *tree, config_t *config);

#endif // !__SPR_H__
