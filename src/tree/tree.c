#include "tree.h"
#include <sequence-alignment/sequence-alignment.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Create a new tree.
tree_t *newTree(alignment_t *alignment) {
  tree_t *t = malloc(sizeof(tree_t));
  t->alignment = alignment;

  // Allocate space for all edge annotations in a single call
  int32_t *arrays = malloc(3 * (2 * alignment->taxa - 1) * sizeof(int32_t));
  for (int i = 0; i < 3 * (2 * alignment->taxa - 1); i++)
    arrays[i] = NULL_EDGE;
  t->parent = arrays;
  t->left = arrays + 2 * alignment->taxa - 1;
  t->right = arrays + 2 * (2 * alignment->taxa - 1);

  t->internalSequences = newSequenceArray(
      alignment->taxa - 1, alignment->characters, alignment->states);

  return t;
}

// Return the number of nodes in the tree.
uint32_t treeNodes(tree_t *tree) { return 2 * tree->alignment->taxa - 1; }

// Return the number of leaf nodes in the tree.
uint32_t treeLeaves(tree_t *tree) { return tree->alignment->taxa; }

// Return the number of internal nodes in the tree.
uint32_t treeInternalNodes(tree_t *tree) { return tree->alignment->taxa - 1; }

// Returns the index of the first leaf on the tree.
uint32_t firstLeaf(tree_t *tree) { return tree->alignment->taxa - 1; }

// Create a new array of trees from the same alignment.
tree_t *newTreeArray(uint32_t n, alignment_t *alignment) {
  tree_t *trees = malloc(n * sizeof(tree_t));

  // All trees point to the same alignment
  for (int i = 0; i < n; i++)
    trees[i].alignment = alignment;

  // Allocate space for all edge annotations for all trees in a single call
  int32_t *arrays = malloc(n * 3 * treeNodes(&trees[0]) * sizeof(int32_t));
  for (int i = 0; i < n * 3 * (2 * alignment->taxa - 1); i++)
    arrays[i] = NULL_EDGE;

  // Set tree annotations for all trees from the single memory space
  for (int i = 0; i < n; i++) {
    trees[i].parent = arrays + (3 * i) * treeNodes(trees);
    trees[i].left = arrays + (3 * i + 1) * treeNodes(trees);
    trees[i].right = arrays + (3 * i + 2) * treeNodes(trees);
  }

  // Every tree will have independent internal sequences
  trees[0].internalSequences = newSequenceArray(
      n * treeInternalNodes(trees), alignment->characters, alignment->states);
  for (int i = 0; i < n; i++)
    trees[i].internalSequences =
        trees[0].internalSequences + i * treeInternalNodes(trees);

  return trees;
}

// Return true if node is leaf, false otherwise.
bool isLeaf(tree_t *tree, int node) { return node >= firstLeaf(tree); }

// Return true if all nodes of both trees have the same edges, false
// otherwise. IMPORTANT: It is not an accurate comparison of equality between
// trees
bool areEqual(tree_t *t1, tree_t *t2) {
  if (t1 == t2)
    return 1;

  if (t1->alignment != t2->alignment)
    return 0;

  for (int i = 1; i < treeNodes(t1); i++)
    if (t1->parent[i] != t2->parent[i])
      return false;
  return true;
}

// Search a node by its label.
int searchNodeByLabel(tree_t *tree, const char *label) {
  for (int i = 0; i < treeLeaves(tree); i++)
    if (!strncmp(tree->alignment->labels[i], label, LABEL_SIZE))
      return firstLeaf(tree) + i;
  return NULL_EDGE;
}

// Arrange the tree as the smallest possible tree (3 OTUs + 1 internal HTU +
// root) from an alignment
tree_t *smallestTree(tree_t *tree) {
  // Set edge between the first taxon and the "root"
  tree->parent[firstLeaf(tree)] = 0;
  tree->left[0] = firstLeaf(tree);

  // Set left edge of the HTU to the second taxon
  tree->parent[firstLeaf(tree) + 1] = 1;
  tree->left[1] = firstLeaf(tree) + 1;

  // Set right edge of the HTU to the third taxon
  tree->parent[firstLeaf(tree) + 2] = 1;
  tree->right[1] = firstLeaf(tree) + 2;

  // Create an edge between nodes 0 and 1
  tree->parent[1] = 0;
  tree->right[0] = 1;

  // Set all other edges to be invalid
  tree->parent[0] = NULL_EDGE;
  for (int i = 2; i < firstLeaf(tree); i++)
    tree->parent[i] = NULL_EDGE;
  for (int i = firstLeaf(tree) + 3; i < treeNodes(tree); i++)
    tree->parent[i] = NULL_EDGE;
  for (int i = 2; i < treeNodes(tree); i++) {
    tree->left[i] = NULL_EDGE;
    tree->right[i] = NULL_EDGE;
  }

  return tree;
}

// Print tree internal structure.
void printTree(tree_t *tree) {
  char newickBuffer[LABEL_SIZE * LABEL_SIZE];
  printNewick(tree, newickBuffer);
  printf("Newick: %s;\n", newickBuffer);

  printf("Parent array: [");
  for (int i = 0; i < treeNodes(tree); i++)
    printf("\t%d", tree->parent[i]);
  printf("\t]\n");

  printf("Left array: [");
  for (int i = 0; i < treeNodes(tree); i++)
    printf("\t%d", tree->left[i]);
  printf("\t]\n");

  printf("Right array: [");
  for (int i = 0; i < treeNodes(tree); i++)
    printf("\t%d", tree->right[i]);
  printf("\t]\n");

  printf("Internal Sequences:\n");
  for (int i = 0; i < firstLeaf(tree); i++) {
    printf("%d :", i);
    printSequence(tree->internalSequences[i], tree->alignment->characters,
                  tree->alignment->states);
  }
}

// Print a node in Newick format, keeping track of origin of call.
uint64_t printNewickNode(tree_t *tree, uint32_t node, char *buffer) {
  if (node == NULL_EDGE)
    return 0;

  if (isLeaf(tree, node)) {
    return sprintf(buffer, "%s",
                   tree->alignment->labels[node - firstLeaf(tree)]);
  }

  uint64_t bytesWritten = 0;
  bytesWritten += sprintf(buffer, "(");
  bytesWritten +=
      printNewickNode(tree, tree->left[node], buffer + bytesWritten);
  bytesWritten += sprintf(buffer + bytesWritten, ",");
  bytesWritten +=
      printNewickNode(tree, tree->right[node], buffer + bytesWritten);
  bytesWritten += sprintf(buffer + bytesWritten, ")");

  return bytesWritten;
}

// Print tree in Newick format as rooted and without final ";".
uint64_t printNewick(tree_t *tree, char *buffer) {
  if (!tree)
    return 0;

  return printNewickNode(tree, 0, buffer);
}

// Copy treeSrc to treeDst inplace
void copyTree(tree_t *treeSrc, tree_t *treeDst) {
  treeDst->alignment = treeSrc->alignment;
  memcpy(treeDst->parent, treeSrc->parent,
         3 * treeNodes(treeSrc) * sizeof(uint32_t));
  memcpy(**(treeDst->internalSequences), **(treeSrc->internalSequences),
         treeInternalNodes(treeSrc) * treeSrc->alignment->states *
             allowedArraySize(treeSrc->alignment->characters));
}

// Delete tree.
void destroyTree(tree_t *tree) {
  if (!tree)
    return;

  free(tree->internalSequences[0][0]);
  free(tree->internalSequences[0]);
  free(tree->internalSequences);
  free(tree->parent);
  free(tree);
}

// Delete an array of trees allocated by newTreeArray.
void destroyTreeArray(tree_t *treeArray) {
  free(treeArray->internalSequences[0][0]);
  free(treeArray->internalSequences[0]);
  free(treeArray->internalSequences);
  free(treeArray->parent);
  free(treeArray);
}
