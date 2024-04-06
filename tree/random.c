#include "random.h"

#include "tree.h"
#include <sequence-alignment/sequence-alignment.h>
#include <stdlib.h>
#include <time.h>

// Linked list auxiliary struct
typedef struct list {
  struct list *next;
  node_t *node;
} list_t;

// Create a new list node
list_t *newListNode(node_t *node) {
  list_t *l = malloc(sizeof(list_t));
  l->node = node;
  l->next = NULL;
  return l;
}

// Append the tree node to linked list
void appendToList(list_t **list, node_t *node) {
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
node_t *removeNodeAtIndex(list_t **list, int i) {
  if (!list || !*list)
    return NULL;

  list_t *tmp = *list;
  node_t *removedNode = NULL;

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
    return NULL;

  // Remove required node and fix pointers
  list_t *next = tmp->next->next;
  removedNode = tmp->next->node;
  free(tmp->next);
  tmp->next = next;

  return removedNode;
}

// Generate a random unrooted binary tree from alignment
tree_t *randomUnrootedBinaryTree(alignment_t alignment,
                                 alignment_t auxAlignment) {
  int numSpecies = getAlignmentSize();
  int auxAlignmentIndex = 0;

  // Populate node list with all taxa and predecessor internal nodes
  list_t *nodeList = NULL;
  for (int i = 0; i < numSpecies; i++) {
    node_t *node = nodeWithPredecessor(alignment[i].label);
    node->out->info->sequence = alignment + i;
    appendToList(&nodeList, node);
  }

  // Seed for RNG
  srand(time(NULL));

  while (numSpecies > 3) {
    // Set common info struct for all new generated nodes
    info_t *commonInfo = newInfo();
    commonInfo->sequence = auxAlignment + auxAlignmentIndex;
    auxAlignmentIndex++;

    // Sample first random node
    int index1 = rand() % numSpecies;
    node_t *node1 = removeNodeAtIndex(&nodeList, index1);
    node1->info = commonInfo;

    // Decrement species amount for sampling without replacement
    numSpecies--;

    // Sample second random node
    // This sampling will remove and introduce a new node, so no need to
    // decrement counter
    int index2 = rand() % numSpecies;
    node_t *node2 = removeNodeAtIndex(&nodeList, index2);
    node2->info = commonInfo;

    // Create the new internal node
    node_t *newInternalNode = newNode(commonInfo);
    newInternalNode->out = newNode(NULL);
    newInternalNode->out->out = newInternalNode;

    // Set relations on new internal node
    newInternalNode->next = node1;
    node1->next = node2;
    node2->next = newInternalNode;

    // Append new internal node to list
    appendToList(&nodeList, newInternalNode->out);
  }

  // Create the last internal ring
  node_t *node1 = removeNodeAtIndex(&nodeList, 0);
  node_t *node2 = removeNodeAtIndex(&nodeList, 0);
  node_t *node3 = removeNodeAtIndex(&nodeList, 0);

  node1->next = node2;
  node2->next = node3;
  node3->next = node1;

  // Set common info struct for all new generated nodes
  info_t *commonInfo = newInfo();
  commonInfo->sequence = auxAlignment + auxAlignmentIndex;

  node1->info = commonInfo;
  node2->info = commonInfo;
  node3->info = commonInfo;

  return node1;
}
