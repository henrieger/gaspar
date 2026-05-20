#ifndef __PARSIMONY_H__
#define __PARSIMONY_H__

#include <config.h>
#include <stdint.h>
#include <tree/tree.h>

// Calculate Wagner parsimony of a tree using Fitch's algorithm (Fitch, 1971).
double fitchParsimony(tree_t *tree, config_t *config);

// Calculate Wagner parsimony at a particular node of the tree
double localParsimony(tree_t *tree, int32_t node);

void initializeGlobalAuxSequences(uint32_t characters, uint32_t states);
void destroyGlobalAuxSequences();

void resetParsimonyCalls();
unsigned long getParsimonyCalls();

#endif // !__PARSIMONY_H__
