#include "random.h"

#include "tree.h"
#include <sequence-alignment/sequence-alignment.h>
#include <stdint.h>
#include <stdlib.h>

// Linked list auxiliary struct
typedef struct list {
  struct list *next;
  int node;
} list_t;

// Create a new list node
list_t *newListNode(int node) {
  list_t *l = malloc(sizeof(list_t));
  l->node = node;
  l->next = NULL;
  return l;
}

// Append the tree node to linked list
void appendToList(list_t **list, int node) {
  list_t *newMember = newListNode(node);
  if (!list || !*list) {
    *list = newMember;
    return;
  }

  // Retrieve end of the list
  list_t *end;
  for (end = *list; end->next != NULL; end = end->next)
    ;

  end->next = newMember;
}

// Remove the node from linked list at index i and return tree node
int removeNodeAtIndex(list_t **list, int i) {
  if (!list || !*list)
    return -1;

  list_t *tmp = *list;
  int removedNode;

  // If item is the first on the list, remove it already
  if (i == 0) {
    removedNode = tmp->node;
    *list = tmp->next;
    free(tmp);
    return removedNode;
  }

  // Iterate to predecessor of position
  for (int j = 1; tmp && j < i; j++) {
    tmp = tmp->next;
  }

  if (!tmp || !(tmp->next))
    return -1;

  // Remove required node and fix pointers
  list_t *next = tmp->next->next;
  removedNode = tmp->next->node;
  free(tmp->next);
  tmp->next = next;

  return removedNode;
}

// Generate a random unrooted binary tree from alignment.
void randomTree(tree_t *tree) {
  // Populate node list with all taxa
  list_t *nodeList = NULL;
  for (int i = firstLeaf(tree) + 1; i < treeNodes(tree); i++) {
    appendToList(&nodeList, i);
  }

  // Do until there is only one node left on list
  for (int i = 1; i < tree->alignment->taxa; i++) {
    // Sample first random node
    uint32_t index1 = rand() % (tree->alignment->taxa - i);
    uint32_t node1 = removeNodeAtIndex(&nodeList, index1);

    // Sample second random node
    uint32_t index2 = rand() % (tree->alignment->taxa - i - 1);
    uint32_t node2 = removeNodeAtIndex(&nodeList, index2);

    // Create the new internal node
    tree->parent[node1] = i;
    tree->parent[node2] = i;
    tree->left[i] = node1;
    tree->right[i] = node2;

    // Append new internal node to list
    appendToList(&nodeList, i);
  }

  // Create the last internal node
  uint32_t lastNode = removeNodeAtIndex(&nodeList, 0);
  tree->left[0] = firstLeaf(tree);
  tree->right[0] = lastNode;
  tree->parent[0] = NULL_EDGE;
}

// Return a random node index on the tree.
inline uint32_t randomNode(tree_t *tree) { return rand() % treeNodes(tree); }

// Return a random internal node index on the tree
inline uint32_t randomInternalNode(tree_t *tree) {
  return rand() % treeInternalNodes(tree);
}

// Return a random internal edge of node
int randomInternalEdge(tree_t *tree, int node) {
  int edge = rand() % 3;
  int result = tree->nodes[node].edges[2];

  // Only need to check for at most 2 extra edges as at least one will point to
  // an internal node
  for (int i = 0; i < 3; i++) {
    if (edge == 0)
      result = tree->nodes[node].edges[0];
    else if (edge == 1)
      result = tree->nodes[node].edges[1];
    else
      result = tree->nodes[node].edges[2];

    // If the node is invalid, try the next edge
    if (result < 0 || isLeaf(tree, result))
      edge = (edge + 1) % 3;
    else
      break;
  }

  return result;
}

void randomSubtreeRecursive(tree_t *tree, int node, int from, int *subtree1,
                            int *subtree2, double probability) {
  if (node < 0)
    return;

  if (*subtree1 >= 0 && *subtree2 >= 0)
    return;

  if ((double)rand() / (double)RAND_MAX < probability) {
    *subtree1 = node;
    *subtree2 = randomEdge(tree, node);
    return;
  } else {
    if (tree->nodes[node].edges[0] != from)
      randomSubtreeRecursive(tree, tree->nodes[node].edges[0], node, subtree1,
                             subtree2, probability);
    if (tree->nodes[node].edges[1] != from)
      randomSubtreeRecursive(tree, tree->nodes[node].edges[1], node, subtree1,
                             subtree2, probability);
    if (tree->nodes[node].edges[1] != from)
      randomSubtreeRecursive(tree, tree->nodes[node].edges[1], node, subtree1,
                             subtree2, probability);
  }
}

// Return the edge of a random subtree from the given edge
void randomSubtree(tree_t *tree, int node, int *subtree1, int *subtree2,
                   double probability) {
  // Initialize return variables if not yet initialized
  *subtree1 = *subtree2 = -1;

  randomSubtreeRecursive(tree, node, -1, subtree1, subtree2, probability);

  // If random process didn't retrieve an edge, get the first one
  if (*subtree1 < 0 || *subtree2 < 0) {
    *subtree1 = node;
    if (tree->nodes[node].edges[0] >= 0)
      *subtree2 = tree->nodes[node].edges[0];
    else if (tree->nodes[node].edges[1] >= 0)
      *subtree2 = tree->nodes[node].edges[1];
    else if (tree->nodes[node].edges[2] >= 0)
      *subtree2 = tree->nodes[node].edges[2];
  }
}
