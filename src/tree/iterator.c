#include "iterator.h"

#include <stdint.h>
#include <stdlib.h>
#include <tree/tree.h>

// Creates a new iterator for a substree rooted in given node.
treeIterator *newSubtreeIterator(tree_t *tree, uint32_t root) {
  treeIterator *it = malloc(sizeof(treeIterator));
  it->tree = tree;
  it->root = root;
  it->next = root;
  it->visited = calloc((2 * tree->alignment->taxa - 1), sizeof(int32_t));

  return it;
}

// Creates a new iterator for the whole tree.
treeIterator *newTreeIterator(tree_t *tree) {
  return newSubtreeIterator(tree, 0);
}

// Resets the iterator to its root.
void resetTreeIterator(treeIterator *it) {
  it->next = it->root;
  for (int i = 0; i < treeNodes(it->tree); i++) {
    it->visited[i] = 0;
  }
}

// Returns next node of the subtree.
int32_t nextTreeIterator(treeIterator *it) {
  // Retrieve the next node as the current node
  int32_t current = it->next;

  // Search depth-first, pre-order for the next node
  bool foundNext = false;
  while (!foundNext) {
    current = it->next;
    it->visited[current]++;

    switch (it->visited[current]) {
    // First visit: return self and make left node the next
    case 1:
      foundNext = true;
      it->next = it->tree->left[current] == NULL_EDGE
                     ? it->tree->parent[current]
                     : it->tree->left[current];
      break;
    // Second visit: already passed here, don't return and go right
    case 2:
      it->next = it->tree->right[current];
      break;
    // Thid visit, last one: go back to parent, or stop if root
    case 3:
      if (current == it->root) {
        it->next = NULL_EDGE;
        return NULL_EDGE;
      }
      it->next = it->tree->parent[current];
      break;
    // Uhh how did you get here
    default:
      it->next = NULL_EDGE;
      return NULL_EDGE;
    }
  }

  return current;
}

// Destroy the iterator.
void destroyIterator(treeIterator *it) {
  free(it->visited);
  free(it);
}
