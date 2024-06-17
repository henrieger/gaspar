#ifndef __PARSIMONY_H__
#define __PARSIMONY_H__

#include <tree/tree.h>
#include <config.h>

// Calculate Wagner parsimony of a tree using Fitch's algorithm (Fitch, 1971).
int fitchParsimony(tree_t *tree, config_t *config);

void initializeGlobalAuxSequences();
void destroyGlobalAuxSequences();

void resetParsimonyCalls();
unsigned long getParsimonyCalls();

#endif // !__PARSIMONY_H__
