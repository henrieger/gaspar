#ifndef __TREE_H__
#define __TREE_H__

#include <gaspar/sequence-alignment/sequence-alignment.h>

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#define NULL_EDGE -1

typedef struct tree {
  int32_t *parent, *left, *right;
  alignment_t *alignment;
  stateAllowedMask_t ***internalSequences;
} tree_t;

// Create a new tree.
tree_t *newTree(alignment_t *alignment);

// Return the number of nodes in the tree.
uint32_t treeNodes(tree_t *tree);

// Return the number of leaf nodes in the tree.
uint32_t treeLeaves(tree_t *tree);

// Return the number of internal nodes in the tree.
uint32_t treeInternalNodes(tree_t *tree);

// Returns the index of the first leaf on the tree.
uint32_t firstLeaf(tree_t *tree);

// Create a new array of trees from the same alignment.
tree_t *newTreeArray(uint32_t n, alignment_t *alignment);

// Return true if node is leaf, false otherwise.
bool isLeaf(tree_t *tree, int32_t node);

// Return true if node 1 is ancestor of node 2.
bool isAncestor(tree_t *tree, int32_t n1, int32_t n2);

// Return true if node 1 and node 2 are sister nodes.
bool isSisterNode(tree_t *tree, int32_t n1, int32_t n2);

// Return true if all internal nodes of both trees have the same edges, false
// otherwise. IMPORTANT: It is not an accurate comparison of equality between
// trees
bool areEqual(tree_t *t1, tree_t *t2);

// Search a node by its label.
int32_t searchNodeByLabel(tree_t *tree, const char *label);

// Create the smallest possible tree (3 OTUs + 1 root HTU) from an alignment
tree_t *smallestTree(tree_t *tree);

// Print tree internal structure.
void printTree(tree_t *tree);

// Print tree in Newick format as rooted and without final ";".
uint64_t printNewick(tree_t *tree, char *buffer);

// Copy treeSrc to treeDst inplace
void copyTree(tree_t *treeSrc, tree_t *treeDst);

// Delete tree.
void destroyTree(tree_t *tree);

// Delete an array of trees allocated by newTreeArray.
void destroyTreeArray(tree_t *treeArray);

#endif // !__TREE_H__
