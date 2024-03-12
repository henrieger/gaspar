#include "tree.h"
#include <sequence-alignment/sequence-alignment.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Create a new node.
node_t *newNode(info_t *info) {
  node_t *n = calloc(1, sizeof(node_t));
  if (info)
    n->info = info;
  return n;
}

// Create info of node.
info_t *newInfo() {
  info_t *info = malloc(sizeof(info_t));
  info->sequence = NULL;
  info->name = NULL;
  info->validSequence = 0;
  info->parsimonyScore = 0;
  return info;
}

// Returns the size of the ring formed by an "internal node"
int ringSize(node_t *node) {
  if (!node)
    return 0;

  if (!node->next)
    return 1; // leaf node

  int size = 1;
  for (node_t *n = node->next; n != node; n = n->next)
    size++;

  return size;
}

// Create a new node and its predecessor. Returns pointer to predecessor.
node_t *nodeWithPredecessor(char *name) {
  node_t *tip = newNode(newInfo());
  node_t *ancestor = newNode(NULL);

  tip->info->name = name;
  tip->out = ancestor;
  ancestor->out = tip;

  return ancestor;
}

// Create the smallest possible unrooted tree with three leaves.
tree_t *smallUnrootedTree(char *a, char *b, char *c) {
  node_t *ancestorA = nodeWithPredecessor(a);
  node_t *ancestorB = nodeWithPredecessor(b);
  node_t *ancestorC = nodeWithPredecessor(c);

  ancestorA->next = ancestorB;
  ancestorB->next = ancestorC;
  ancestorC->next = ancestorA;

  info_t *ancestorInfo = newInfo();
  ancestorA->info = ancestorInfo;
  ancestorB->info = ancestorInfo;
  ancestorC->info = ancestorInfo;

  return ancestorA;
}

// Return TRUE if node is leaf, FALSE otherwise.
inline uint8_t isLeaf(node_t *node) { return node->next == NULL; }

// Adds a child to current node.
void addChild(node_t *node, char *name) {
  node_t *oldNext = node->next;
  node->next = nodeWithPredecessor(name);
  node->next->info = node->info;
  node->next->next = oldNext;
}

// Create a brother to node with one empty end
node_t *addAnonymousBrother(node_t *node) {
  // Create a new ring
  info_t *ringInfo = newInfo();
  node_t *ringStart = newNode(ringInfo);
  ringStart->next = newNode(ringInfo);
  ringStart->next->next = newNode(ringInfo);
  ringStart->next->next->next = ringStart;

  // Connect ends of ring to edge
  node_t *oldOut = node->out;
  ringStart->out = node;
  node->out = ringStart;
  oldOut->out = ringStart->next;
  ringStart->next->out = oldOut;

  // Return reference to remaining end of the node
  return ringStart->next->next;
}

// Adds a brother to current node, splitting its branch. Returns a pointer to
// new brother.
node_t *addBrother(node_t *node, char *name) {
  // Creates two disconnected new nodes between current node and its neighbor
  node_t *oldOut = node->out;
  node->out = newNode(NULL);
  oldOut->out = newNode(NULL);

  // Creates brother with predecessor and closes new ring
  node_t *brotherPredecessor = nodeWithPredecessor(name);
  node->out->next = brotherPredecessor;
  brotherPredecessor->next = oldOut->out;
  oldOut->out->next = node->out;

  // Connects new ring to same info
  info_t *newNodeInfo = newInfo();
  newNodeInfo->sequence = NULL;
  brotherPredecessor->info = newNodeInfo;
  brotherPredecessor->next->info = newNodeInfo;
  oldOut->out->next->info = newNodeInfo;

  // Assigns remaining out connections of ring
  node->out->out = node;
  oldOut->out->out = oldOut;

  // Return pointer to brother
  return brotherPredecessor->out;
}

// Copy a node info
info_t *copyNodeInfo(node_t *node) {
  if (!node || !node->info)
    return NULL;

  info_t *newNodeInfo = newInfo();
  memcpy(newNodeInfo, node->info, sizeof(info_t));

  return newNodeInfo;
}

// Copy a node recursevely, keeping track of origin of call.
tree_t *copyRecursive(tree_t *tree, node_t *from) {
  if (!tree)
    return NULL;

  tree_t *newTree = newNode(NULL);
  newTree->info = copyNodeInfo(tree);

  if (tree->out && from != tree->out) {
    newTree->out = copyRecursive(tree->out, tree);
    newTree->out->out = newTree;
  }

  node_t *nodeIter = newTree;
  for (node_t *n = tree->next; n && n != tree; n = n->next) {
    node_t *newNodeInRing = newNode(newTree->info);
    node_t *newNodeOut = copyRecursive(n->out, n);
    newNodeInRing->out = newNodeOut;
    newNodeOut->out = newNodeInRing;
    nodeIter->next = newNodeInRing;
    nodeIter = newNodeInRing;
  }
  if (nodeIter != newTree)
    nodeIter->next = newTree;

  return newTree;
}

// Returns a copy of the tree.
tree_t *copyTree(tree_t *tree) { return copyRecursive(tree, NULL); }

// Prunes a node from tree and returns the new tree as unrooted.
tree_t *prune(node_t *node) {
  node_t *newTree = node->out;
  newTree->out = NULL;
  node->out = NULL;
  return unrootTree(newTree);
}

// Graft a subtree into a tree. Assumes subtree as rooted.
void graft(tree_t *tree, tree_t *subtree) {
  if (!tree || !subtree)
    return;

  if (!tree->out) {
    // Add subtree to old root
    tree->out = subtree;
    subtree->out = tree;
  } else {
    // Create a new node and graft as brother of tree
    node_t *newNode = addAnonymousBrother(tree);
    newNode->out = subtree;
    subtree->out = newNode;
  }
}

// Free space of node info.
void destroyInfo(info_t *info) {
  if (!info)
    return;

  free(info);
}

// Free space of node.
inline void destroyNode(node_t *node) { free(node); }

// Delete subtrees recursevely, keeping track of origin of call.
void destroyRecursive(node_t *node) {
  if (!node)
    return;

#ifdef DEBUG
  printf("Removing node %s\n", node->info->name);
#endif

  if (!isLeaf(node)) {
    node_t *next = node->next;
    while (next != node) {
#ifdef DEBUG
      printf("Removing node in loop %s\n", next->info->name);
#endif
      destroyRecursive(next->out);
      node_t *oldNext = next;
      next = next->next;
      destroyNode(oldNext);
    }
  }

  destroyInfo(node->info);
  destroyNode(node);
}

// Delete tree recursevely.
void destroyTree(tree_t *tree) {
  if (!tree)
    return;
#ifdef DEBUG
  printf("Removing tree at %p ", tree);
  printTree(tree);
  printf("\n");
#endif
  if (tree->out)
    destroyRecursive(tree->out);
  destroyRecursive(tree);
#ifdef DEBUG
  printf("Tree at %p removed successfully\n", tree);
#endif
}

// Print a node, keeping track of origin of call.
void printNode(node_t *node) {
  if (node->info->name)
    printf("%s", node->info->name);

  if (!isLeaf(node)) {
    printf("(");
    node_t *next = node->next;
    while (next != node) {
      printNode(next->out);
      next = next->next;
      if (next != node)
        printf(",");
    }
    printf(")");
  }
}

// Print tree in Newick format as rooted.
void printTree(tree_t *tree) {
  if (tree->out) {
    printf("(");
    printNode(tree->out);
    printf(",");
    printNode(tree);
    printf(")");
  } else {
    printNode(tree);
    // printf(";");
  }
}

// Search node by its name, keeping track of origin of call.
node_t *searchNodeByNameRecursive(tree_t *tree, const char *name,
                                  node_t *from) {
  if (!tree)
    return NULL;

  if (tree->info->name && !strcmp(tree->info->name, name))
    return tree;

  node_t *answer = NULL;

  if (from != tree->out)
    answer = searchNodeByNameRecursive(tree->out, name, tree);

  for (node_t *n = tree->next; !answer && n && n != tree; n = n->next)
    answer = searchNodeByNameRecursive(n->out, name, n);

  return answer;
}

// Search a node by its name.
tree_t *searchNodeByName(tree_t *tree, const char *name) {
  return searchNodeByNameRecursive(tree, name, NULL);
}

// Root tree based on reference node. Returns new root.
tree_t *rootTree(node_t *node) {
  info_t *rootInfo = newInfo();

  node_t *root = newNode(rootInfo);
  node_t *oldOut = node->out;

  root->next = newNode(rootInfo);
  root->next->out = oldOut;
  oldOut->out = root->next;

  root->next->next = newNode(rootInfo);
  root->next->next->out = node;
  node->out = root->next->next;
  root->next->next->next = root;

  return root;
}

// Unroot tree. Assumes passed node is the root. Returns a pointer to new
// reference point on tree.
tree_t *unrootTree(node_t *root) {
  // Check if tree is already unrooted
  if (root->out)
    return root;

  // If node is a politomy, just remove the extra node
  if (ringSize(root) > 3) {
    node_t *newReferencePoint = root->next;
    node_t *ringEnd = newReferencePoint;
    while (ringEnd->next != root)
      ringEnd = ringEnd->next;
    ringEnd->next = newReferencePoint;
    destroyNode(root);
    return newReferencePoint;
  }

  // Remove root and the corresponding branches
  node_t *left = root->next->out;
  node_t *right = root->next->next->out;
  destroyInfo(root->info);
  destroyNode(left->out);
  destroyNode(right->out);
  destroyNode(root);
  left->out = right;
  right->out = left;
  return left;
}
