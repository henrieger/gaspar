#ifndef __TREE_H__
#define __TREE_H__

#include <stdint.h>

typedef struct info {
  const char *name;
} info_t;

typedef struct node {
  struct node *out;
  struct node *next;
  info_t *info; 
} node_t;

#define tree_t node_t

#define POSTORDER       0b00000001
#define BREADTH_FIRST   0b00000010

// Create a new node.
node_t *newNode();

// Create info of node.
info_t *newInfo();

// Create the smallest possible unrooted tree with three leaves.
tree_t *smallUnrootedTree(const char *a, const char *b, const char *c);

// Return TRUE if node is leaf, FALSE otherwise
uint8_t isLeaf(node_t *node);

// Adds a child to current node
void addChild(node_t *node, const char *name);

// Adds a brother to current node, splitting its branch
void addBrother(node_t *node, const char *name);

// Free space of node.
void deleteNode(node_t *node);

// Free space of node info.
void deleteInfo(info_t *info);

// Delete tree recursevely.
void deleteTree(tree_t *tree);

// Print tree in Newick format as rooted
void printTree(tree_t *tree);

// Root tree based on reference node. Returns new root.
tree_t *rootTree(node_t *node);

#endif
