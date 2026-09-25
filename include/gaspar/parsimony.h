#ifndef __LIBGASPAR_PARSIMONY_H__
#define __LIBGASPAR_PARSIMONY_H__

#include <gaspar/config.h>
#include <gaspar/tree.h>

#include <stdint.h>

// Calculate Wagner parsimony of a tree using Fitch's algorithm (Fitch, 1971).
double fitchParsimony(tree_t *tree, config_t *config);

// Calculate Wagner parsimony at a particular node of the tree
double localParsimony(tree_t *tree, int32_t node);

#endif // !__LIBGASPAR_PARSIMONY_H__
