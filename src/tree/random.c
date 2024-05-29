#include "random.h"

#include "tree.h"
#include <sequence-alignment/sequence-alignment.h>
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
tree_t *randomTree(alignment_t *alignment) {
  tree_t *tree = newTreeFromAlignment(alignment);

  // Populate node list with all taxa
  list_t *nodeList = NULL;
  for (int i = 0; i < tree->leaves; i++) {
    appendToList(&nodeList, i);
  }

  // Do until there are only 3 nodes left on list
  for (int i = 0; i < tree->leaves - 2; i++) {
    // Sample first random node
    int index1 = rand() % (tree->leaves - i);
    int node1 = removeNodeAtIndex(&nodeList, index1);

    // Sample second random node
    int index2 = rand() % (tree->leaves - i - 1);
    int node2 = removeNodeAtIndex(&nodeList, index2);

    // Create the new internal node
    tree->nodes[node1].edge1 = alignment->taxa + i;
    tree->nodes[node2].edge1 = alignment->taxa + i;
    tree->internal[i].edge2 = node1;
    tree->internal[i].edge3 = node2;

    // Append new internal node to list
    appendToList(&nodeList, alignment->taxa + i);
  }

  // Create the last internal node
  int node1 = removeNodeAtIndex(&nodeList, 1);
  int node2 = removeNodeAtIndex(&nodeList, 0);
  tree->nodes[node1].edge1 = node2;
  tree->nodes[node2].edge1 = node1;

  tree->root = tree->size - 1;

  return tree;
}

// Return a random node index on the tree.
inline int randomNode(int size) { return rand() % size; }

// Return a random internal node index on the tree
inline int randomInternalNode(int numLeaves) {
  return (rand() % (numLeaves - 2)) + numLeaves;
}

// Return a random non-null edge of node
int randomEdge(tree_t *tree, int node) {
  int edge = rand() % 3;
  int result = tree->nodes[node].edge3;

  // Only need to check for at most 2 extra edges as at least one will point to
  // an internal node
  for (int i = 0; i < 3; i++) {
    if (edge == 0)
      result = tree->nodes[node].edge1;
    else if (edge == 1)
      result = tree->nodes[node].edge2;
    else
      result = tree->nodes[node].edge3;

    // If the node is invalid, try the next edge
    if (result < 0)
      edge = (edge + 1) % 3;
    else
      break;
  }

  return result;
}

// Return a random internal edge of node
int randomInternalEdge(tree_t *tree, int node) {
  int edge = rand() % 3;
  int result = tree->nodes[node].edge3;

  // Only need to check for at most 2 extra edges as at least one will point to
  // an internal node
  for (int i = 0; i < 3; i++) {
    if (edge == 0)
      result = tree->nodes[node].edge1;
    else if (edge == 1)
      result = tree->nodes[node].edge2;
    else
      result = tree->nodes[node].edge3;

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
    if (tree->nodes[node].edge1 != from)
      randomSubtreeRecursive(tree, tree->nodes[node].edge1, node, subtree1, subtree2,
                    probability);
    if (tree->nodes[node].edge2 != from)
      randomSubtreeRecursive(tree, tree->nodes[node].edge2, node, subtree1, subtree2,
                    probability);
    if (tree->nodes[node].edge2 != from)
      randomSubtreeRecursive(tree, tree->nodes[node].edge2, node, subtree1, subtree2,
                    probability);
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
    if (tree->nodes[node].edge1 >= 0)
      *subtree2 = tree->nodes[node].edge1;
    else if (tree->nodes[node].edge2 >= 0)
      *subtree2 = tree->nodes[node].edge2;
    else if (tree->nodes[node].edge3 >= 0)
      *subtree2 = tree->nodes[node].edge3;
  }
}
