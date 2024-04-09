#ifndef __NNI_H__
#define __NNI_H__

#include <tree/tree.h>

// Create a Nearest Neighbor Interchange operation in the out edge connected to
// node. Select the new joint by integer index (2 possible). Assumes unrooted
// binary tree. Leaves not accepted as input.
void nni(node_t *n, int joint);

// Do a random NNI operation on the tree
void randomNNI(tree_t *tree);

#endif // !__NNI_H__
