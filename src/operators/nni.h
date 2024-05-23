#ifndef __NNI_H__
#define __NNI_H__

#include <tree/tree.h>
#include <config.h>

// Create a Nearest Neighbor Interchange operation in the out edge connected to
// node. Select the new joint by integer index (2 possible). Assumes unrooted
// binary tree. Leaves not accepted as input.
void nni(tree_t *tree, int n1, int n2, int joint);

// Do a random NNI operation on the tree
void randomNNI(tree_t *tree, config_t *config);

#endif // !__NNI_H__
