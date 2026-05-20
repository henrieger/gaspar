#ifndef __BRANCH_SWAP_H__
#include <config.h>
#include <stdint.h>
#include <tree/tree.h>

void subtreeSwap(tree_t *tree, uint32_t n1, uint32_t n2);

void randomSubtreeSwap(tree_t *tree, config_t *config);

#endif // !__BRANCH_SWAP_H__
