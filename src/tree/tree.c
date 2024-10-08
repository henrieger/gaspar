#include "tree.h"
#include <sequence-alignment/sequence-alignment.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Create a new node.
node_t *newNode(sequence_t *sequence, const char *label) {
  node_t *n = malloc(sizeof(node_t));
  n->sequence = sequence;
  n->label = label;
  n->edge1 = n->edge2 = n->edge3 = -1;
  return n;
}

// Create a new tree.
tree_t *newTree(unsigned int leaves) {
  tree_t *t = malloc(sizeof(tree_t));
  t->leaves = leaves;
  t->size = 2 * leaves - 2;

  t->nodes = malloc(t->size * sizeof(node_t));
  for (int i = 0; i < t->size; i++) {
    t->nodes[i].edge1 = t->nodes[i].edge2 = t->nodes[i].edge3 = -1;
    t->nodes[i].label = NULL;
    t->nodes[i].sequence = NULL;
  }

  t->internal = t->nodes + leaves;

  return t;
}

// Create a new tree from data in alignment.
tree_t *newTreeFromAlignment(alignment_t *alignment) {
  // Create new tree and set leaf data as the alignment data
  tree_t *t = newTree(alignment->taxa);
  for (int i = 0; i < alignment->taxa; i++) {
    t->nodes[i].sequence = &(alignment->sequences[i]);
    t->nodes[i].label = alignment->labels[i];
  }

  // Allocate internal sequences
  sequence_t *auxSequences = newSequenceArray(alignment->taxa - 2);
  for (int i = 0; i < alignment->taxa - 2; i++) {
    t->internal[i].sequence = &(auxSequences[i]);
  }

  // Set root arbitrarily to last leaf
  t->root = alignment->taxa - 1;

  return t;
}

// Returns the degree of the node
int nodeDegree(tree_t *tree, int node) {
  if (node < 0)
    return 0;

  int sum = 0;

  if (tree->nodes[node].edge1 >= 0)
    sum++;
  if (tree->nodes[node].edge2 >= 0)
    sum++;
  if (tree->nodes[node].edge3 >= 0)
    sum++;

  return sum;
}

// Return TRUE if node is leaf, FALSE otherwise.
uint8_t isLeaf(tree_t *tree, int node) { return nodeDegree(tree, node) == 1; }

// Change old edge in node to a new edge, independent of which edge it is
void changeEdge(tree_t *tree, int node, int oldEdge, int newEdge) {
  node_t *nodeStruct = &(tree->nodes[node]);
  if (nodeStruct->edge1 == oldEdge)
    nodeStruct->edge1 = newEdge;
  else if (nodeStruct->edge2 == oldEdge)
    nodeStruct->edge2 = newEdge;
  else if (nodeStruct->edge3 == oldEdge)
    nodeStruct->edge3 = newEdge;
}

// Check if two nodes contain the same edges. Assumes no repetitions.
uint8_t areEqualNodes(node_t *t1, node_t *t2) {
  uint8_t edge1Present = t1->edge1 == t2->edge1 || t1->edge1 == t2->edge2 ||
                         t1->edge1 == t2->edge3;
  uint8_t edge2Present = t1->edge2 == t2->edge1 || t1->edge2 == t2->edge2 ||
                         t1->edge2 == t2->edge3;
  uint8_t edge3Present = t1->edge3 == t2->edge1 || t1->edge3 == t2->edge2 ||
                         t1->edge3 == t2->edge3;
  return edge1Present && edge2Present && edge3Present;
}

// Return TRUE if all internal nodes of both trees have the same edges. FALSE
// otherwise. IMPORTANT: It is not an accurate comparison of equality between
// trees
uint8_t areEqual(tree_t *t1, tree_t *t2) {
  if (t1 == t2)
    return 1;

  if (t1->size != t2->size)
    return 0;

  for (int i = 0; i < t1->leaves - 2; i++)
    if (!areEqualNodes(&(t1->internal[i]), &(t2->internal[i])))
      return 0;
  return 1;
}

// Search a node by its label.
int searchNodeByLabel(tree_t *tree, const char *label) {
  for (int i = 0; i < tree->size; i++)
    if (!strncmp(tree->nodes[i].label, label, LABEL_SIZE))
      return i;
  return -1;
}

// Create the smallest possible tree (3 OTUs + 1 root HTU) from an alignment
tree_t *smallestTree(alignment_t *alignment) {
  // Create new tree from alignment with root as the first HTU
  tree_t *t = newTreeFromAlignment(alignment);
  t->root = alignment->taxa;

  // Set parent of three OTUs as the root
  t->nodes[0].edge1 = t->root;
  t->nodes[1].edge1 = t->root;
  t->nodes[2].edge1 = t->root;

  // Set the children of the root as the OTUs
  t->nodes[t->root].edge1 = 0;
  t->nodes[t->root].edge2 = 1;
  t->nodes[t->root].edge3 = 2;

  return t;
}

// Print tree internal structure.
void printTree(tree_t *tree) {
  printf("Size: %d\nLeaves: %d\nRoot: %d\nNodes array at %p\nInternal nodes "
         "array at %p\nNodes:\n",
         tree->size, tree->leaves, tree->root, tree->nodes, tree->internal);
  for (int i = 0; i < tree->size; i++) {
    printf("\t%d (%s): [%d %d %d]\t", i, tree->nodes[i].label,
           tree->nodes[i].edge1, tree->nodes[i].edge2, tree->nodes[i].edge3);
    printSequence(tree->nodes[i].sequence);
  }
}

// Print a node in Newick format, keeping track of origin of call.
void printNewickNode(tree_t *tree, int node, int from, FILE *fp) {
  if (!tree || node < 0)
    return;

  node_t *nodeStruct = &(tree->nodes[node]);

  if (nodeStruct->label)
    fprintf(fp, "%s", nodeStruct->label);

  if (isLeaf(tree, node))
    return;

  fprintf(fp, "(");
  if (from == nodeStruct->edge1) {
    printNewickNode(tree, nodeStruct->edge2, node, fp);
    fprintf(fp, ",");
    printNewickNode(tree, nodeStruct->edge3, node, fp);
  } else if (from == nodeStruct->edge2) {
    printNewickNode(tree, nodeStruct->edge1, node, fp);
    fprintf(fp, ",");
    printNewickNode(tree, nodeStruct->edge3, node, fp);
  } else if (from == nodeStruct->edge3) {
    printNewickNode(tree, nodeStruct->edge1, node, fp);
    fprintf(fp, ",");
    printNewickNode(tree, nodeStruct->edge2, node, fp);
  }
  fprintf(fp, ")");
}

// Print tree in Newick format as rooted and without final ";".
void printNewick(tree_t *tree, FILE *fp) {
  FILE *finalFile = fp;
  if (!fp)
    finalFile = stdout;

  if (!tree || tree->root < 0)
    return;

  node_t *rootStruct = &(tree->nodes[tree->root]);

  if (rootStruct->label)
    fprintf(finalFile, "%s", rootStruct->label);

  if (isLeaf(tree, tree->root))
    return;

  fprintf(finalFile, "(");
  printNewickNode(tree, tree->root, rootStruct->edge1, finalFile);
  fprintf(finalFile, ",");
  printNewickNode(tree, rootStruct->edge1, tree->root, finalFile);
  fprintf(finalFile, ")");
}

// Returns a copy of the tree.
tree_t *copyTree(const tree_t *tree) {
  tree_t *copy = newTree(tree->leaves);
  copy->root = tree->root;

  sequence_t *copySequenceArray = newSequenceArray(tree->leaves - 2);
  for (int i = 0; i < tree->leaves - 2; i++) {
    for (int j = 0; j < CHAR_STATES; j++) {
      for (int k = 0; k < allowedArraySize(); k++)
        copySequenceArray[i].allowed[j][k] =
            tree->internal[i].sequence->allowed[j][k];
    }
  }

  for (int i = 0; i < tree->leaves; i++)
    copy->nodes[i].sequence = tree->nodes[i].sequence;
  for (int i = 0; i < tree->leaves - 2; i++)
    copy->internal[i].sequence = &(copySequenceArray[i]);

  for (int i = 0; i < tree->size; i++) {
    copy->nodes[i].edge1 = tree->nodes[i].edge1;
    copy->nodes[i].edge2 = tree->nodes[i].edge2;
    copy->nodes[i].edge3 = tree->nodes[i].edge3;
    copy->nodes[i].label = tree->nodes[i].label;
  }

  return copy;
}

// Free space of node.
inline void destroyNode(node_t *node) { free(node); }

// Delete tree.
void destroyTree(tree_t *tree) {
  if (!tree)
    return;

  free(tree->internal[0].sequence->allowed[0]);
  free(tree->internal[0].sequence);
  free(tree->nodes);
  free(tree);
}
