#ifndef __TREE_H__
#define __TREE_H__

#include <stdint.h>
#include <sequence-alignment/sequence-alignment.h>

typedef struct info {
  const char *name;
  sequence_t *sequence;
  int parsimonyScore;
  uint8_t validSequence;
} info_t;

typedef struct node {
  struct node *out;
  struct node *next;
  info_t *info;
} node_t;

#define tree_t node_t

// Create a new node.
node_t *newNode(info_t *info);

// Create info of node.
info_t *newInfo();

// Create the smallest possible unrooted tree with three leaves.
tree_t *smallUnrootedTree(const char *a, const char *b, const char *c);

// Return TRUE if node is leaf, FALSE otherwise.
uint8_t isLeaf(node_t *node);

// Adds a child to current node.
void addChild(node_t *node, const char *name);

// Adds a brother to current node, splitting its branch. Returns a pointer to new brother.
node_t *addBrother(node_t *node, const char *name);

// Returns a copy of the tree.
tree_t *copyTree(tree_t *tree);

// Prunes a node from tree and returns the new tree as rooted.
tree_t *prune(node_t *node);

// Graft a subtree into a tree. Assumes subtree as rooted.
void graft(tree_t *tree, tree_t *subtree);

// Free space of node.
void destroyNode(node_t *node);

// Free space of node info.
void destroyInfo(info_t *info);

// Delete tree recursevely.
void destroyTree(tree_t *tree);

// Print tree in Newick format as rooted.
void printTree(tree_t *tree);

// Search a node by its name.
node_t *searchNodeByName(tree_t *tree, const char *name);

// Root tree based on reference node. Returns new root.
tree_t *rootTree(node_t *node);

// Unroot tree. Assumes passed node is the root. Returns a pointer to new
// reference point on tree.
tree_t *unrootTree(node_t *root);

#endif // !__TREE_H__
