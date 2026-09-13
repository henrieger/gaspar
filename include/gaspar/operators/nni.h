#ifndef __NNI_H__
#define __NNI_H__

#include <gaspar/base/config.h>
#include <gaspar/tree/tree.h>
#include <stdint.h>

// Create a Nearest Neighbor Interchange operation in the out edge connected to
// node. Select the new joint by integer index (2 possible). Assumes unrooted
// binary tree. Leaves not accepted as input.
void nni(tree_t *tree, int32_t n1, int32_t n2, int joint);

// Do a random NNI operation on the tree
void randomNNI(tree_t *tree, config_t *config);

#endif // !__NNI_H__
