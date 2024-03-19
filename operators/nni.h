#ifndef __NNI_H__
#define __NNI_H__

#include <tree/tree.h>

// Create a Nearest Neighbor Interchange operation in the out edge connected to node 
// Select the new joint by integer index (2 possible)
void nni(node_t *n, int joint);

#endif // !__NNI_H__
