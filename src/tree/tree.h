#ifndef __TREE_H__
#define __TREE_H__

#include <sequence-alignment/sequence-alignment.h>
#include <stdint.h>
#include <stdio.h>

typedef struct node {
  int edge1, edge2, edge3;
  sequence_t *sequence;
  const char *label;
} node_t;

typedef struct tree {
  unsigned int size, leaves, root;
  node_t *nodes, *internal;
} tree_t;

// Create a new node.
node_t *newNode(sequence_t *sequence, const char *label);

// Create a new tree.
tree_t *newTree(unsigned int leaves);

// Create a new tree from data in alignment.
tree_t *newTreeFromAlignment(alignment_t *alignment);

// Returns the degree of the node
int nodeDegree(tree_t *tree, int node);

// Return TRUE if node is leaf, FALSE otherwise.
uint8_t isLeaf(tree_t *tree, int node);

// Change old edge in node to a new edge, independent of which edge it is
void changeEdge(tree_t *tree, int node, int oldEdge, int newEdge);

// Search a node by its label.
int searchNodeByLabel(tree_t *tree, const char *label);

// Create the smallest possible tree (3 OTUs + 1 root HTU) from an alignment
tree_t *smallestTree(alignment_t *alignment);

// Print tree internal structure.
void printTree(tree_t *tree);

// Print tree in Newick format as rooted and without final ";".
void printNewick(tree_t *tree, FILE *fp);

// Returns a copy of the tree.
tree_t *copyTree(const tree_t *tree);

// Free space of node.
void destroyNode(node_t *node);

// Delete tree.
void destroyTree(tree_t *tree);

#endif // !__TREE_H__
