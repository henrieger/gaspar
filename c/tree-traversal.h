#ifndef __TREE_TRAVERSAL_H__
#define __TREE_TRAVERSAL_H__

#include <stdint.h>
#include "tree.h"

typedef struct traversal {
  info_t *info;
  struct traversal *next;
} traversal_t;

#define POSTORDER       0b00000001
#define BREADTH_FIRST   0b00000010

// Traverses the tree. Default is DFS pre-order.
// Has flags for post-order and BFS traversals.
// When both are active, performs reverse BFS.
traversal_t *traverse(node_t *node, uint8_t flags);

// Prints the names (if any) of traversed nodes.
void print_traversal(traversal_t *traversal);

// Deletes traversal structure
void deleteTraversal(traversal_t *traversal);

#endif // !__TREE_TRAVERSAL_H__
