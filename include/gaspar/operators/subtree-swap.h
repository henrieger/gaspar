#ifndef __BRANCH_SWAP_H__
#define __BRANCH_SWAP_H__

#include <gaspar/base/config.h>
#include <gaspar/tree/tree.h>

#include <stdint.h>

void subtreeSwap(tree_t *tree, uint32_t n1, uint32_t n2);

void randomSubtreeSwap(tree_t *tree, config_t *config);

#endif // !__BRANCH_SWAP_H__
