#ifndef __ITERATOR_H__
#define __ITERATOR_H__

#include <tree/tree.h>

typedef struct {
  tree_t *tree;
  int32_t root;
  int32_t next;
  int32_t *visited;
} treeIterator;

// Creates a new iterator for a substree rooted in given node.
treeIterator *newSubtreeIterator(tree_t *tree, uint32_t root);

// Creates a new iterator for the whole tree.
treeIterator *newTreeIterator(tree_t *tree);

// Resets the iterator to its root.
void resetTreeIterator(treeIterator *it);

// Returns next node of the subtree.
int32_t nextTreeIterator(treeIterator *it);

// Destroy the iterator.
void destroyIterator(treeIterator *it);

#endif // !__ITERATOR_H__
