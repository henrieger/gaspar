#ifndef __ITERATOR_H__
#define __ITERATOR_H__

#include <tree/tree.h>

typedef struct {
  tree_t *tree;
  int32_t root;
  int32_t next;
  int32_t *visited;
} treeIterator_t;

// Creates a new iterator for a substree rooted in given node.
treeIterator_t *newSubtreeIterator(tree_t *tree, uint32_t root);

// Creates a new iterator for the whole tree.
treeIterator_t *newTreeIterator(tree_t *tree);

// Resets the iterator to its root.
void resetTreeIterator(treeIterator_t *it);

// Returns next node of the subtree.
int32_t nextTreeIterator(treeIterator_t *it);

// Destroy the iterator.
void destroyIterator(treeIterator_t *it);

#endif // !__ITERATOR_H__
