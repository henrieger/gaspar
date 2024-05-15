#include "nni.h"

#include <sequence-alignment/sequence-alignment.h>
#include <stdio.h>
#include <stdlib.h>
#include <tree/random.h>
#include <tree/tree.h>

// Set out pointers of and from n as NULL
void separate(node_t *n) {
  n->out->out = NULL;
  n->out = NULL;
}

// Join two unrooted subtrees
void join(node_t *n, node_t *p) {
  p->out = n;
  n->out = p;
}

// Create a Nearest Neighbor Interchange operation in the out edge connected to
// node. Select the new joint by integer index (2 possible). Assumes unrooted
// binary tree. Leaves not accepted as input.
void nni(node_t *n, int joint) {
  tree_t *subtree1 = n;
  tree_t *subtree2 = n->out;

  // Can't operate directly on leaves
  if (isLeaf(subtree1) || isLeaf(subtree2))
    return;

  // Assume a tree (S1(S,T),S2(U,V))
  tree_t *s = subtree1->next->out;
  tree_t *t = subtree1->next->next->out;
  tree_t *u = subtree2->next->out;
  tree_t *v = subtree2->next->next->out;

  // Separate S from main tree
  separate(s);

  // Based on value of joint (0 or 1) select a new joint
  if (joint == 0) {
    // Put V as brother to T and S as brother to U
    separate(v);
    join(v, t->out->next->next);
    join(s, u->out->next);
  } else if (joint == 1) {
    // Put U as brother to T and S as brother to V
    separate(u);
    join(u, t->out->next->next);
    join(s, v->out->next->next);
  }
}

// Do a random NNI operation on the tree
void randomNNI(tree_t *tree) {
  printf("Applying random NNI to: ");
  printTree(tree);
  printf("\n");

  node_t *node = randomNode(tree, getAlignmentSize());
  int joint = rand() % 2;

  nni(node, joint);
}
