#ifndef __PARSIMONY_H__
#define __PARSIMONY_H__

#include "../tree/tree.h"

// Calculate Wagner parsimony of a tree using Fitch's algorithm (Fitch, 1971).
int fitch_parsimony(tree_t *tree);

#endif // !__PARSIMONY_H__