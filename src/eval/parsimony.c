#include "parsimony.h"

#include <config.h>
#include <sequence-alignment/sequence-alignment.h>
#include <stdio.h>
#include <stdlib.h>
#include <tree/tree.h>

sequence_t *unionSeq;
sequence_t *interSeq;

void initializeGlobalAuxSequences() {
  unionSeq = newSequence();
  interSeq = newSequence();
}

int scoreFromInters(allowed_t *r) {
  int score = 0;
  int bitIndex = 0;

  for (int i = 0; i < allowedArraySize(); i++) {
    allowed_t r_i = r[i];
    for (int j = 0; (j < 8 * sizeof(allowed_t)) && bitIndex < getSequenceSize();
         j++, bitIndex++) {
      score += (r_i & ((allowed_t)1 << j)) ? 0 : getCharacterWeight(bitIndex);
    }
  }

  free(r);
  return score;
}

int localParsimony(tree_t *tree, int n1, int n2, int node) {
  node_t *nodeStruct1 = &(tree->nodes[n1]);
  node_t *nodeStruct2 = &(tree->nodes[n2]);

  for (int i = 0; i < CHAR_STATES; i++) {
    for (int j = 0; j < allowedArraySize(); j++) {
      unionSeq->allowed[i][j] = nodeStruct1->sequence->allowed[i][j] |
                                nodeStruct2->sequence->allowed[i][j];
      interSeq->allowed[i][j] = nodeStruct1->sequence->allowed[i][j] &
                                nodeStruct2->sequence->allowed[i][j];
    }
  }

  allowed_t *r = newAllowedStates();
  for (int i = 0; i < CHAR_STATES; i++) {
    for (int j = 0; j < allowedArraySize(); j++) {
      r[j] |= interSeq->allowed[i][j];
    }
  }

  if (node > 0) {
    for (int i = 0; i < CHAR_STATES; i++) {
      for (int j = 0; j < allowedArraySize(); j++) {
        tree->nodes[node].sequence->allowed[i][j] =
            (interSeq->allowed[i][j] & r[j]) |
            (unionSeq->allowed[i][j] & ~r[j]);
      }
    }
  }

  return scoreFromInters(r);
}

// Calculate parsimony of subtree, keeping track of origin of call.
int fitchParsimonyRecursive(tree_t *tree, int node, int from) {
  if (!tree || node < 0)
    return 0;

  // Leaf result is always equal to 0 (no change within a single node)
  if (isLeaf(tree, node))
    return 0;

  // Auxiliary structures
  int n1, n2;
  n1 = n2 = -1;
  node_t *nodeStruct = &(tree->nodes[node]);

  // Select nodes of recursion based on root
  if (nodeStruct->edge1 == from) {
    n1 = nodeStruct->edge2;
    n2 = nodeStruct->edge3;
  } else if (nodeStruct->edge2 == from) {
    n1 = nodeStruct->edge1;
    n2 = nodeStruct->edge3;
  } else if (nodeStruct->edge3 == from) {
    n1 = nodeStruct->edge1;
    n2 = nodeStruct->edge2;
  }

  return fitchParsimonyRecursive(tree, n1, node) +
         fitchParsimonyRecursive(tree, n2, node) +
         localParsimony(tree, n1, n2, node);
}

// Calculate Wagner parsimony of a tree using Fitch's algorithm (Fitch, 1971).
int fitchParsimony(tree_t *tree, config_t *config) {
  if (!tree)
    return 0;

  int root1 = tree->root;
  int root2 = tree->nodes[tree->root].edge1;

  return fitchParsimonyRecursive(tree, root1, root2) +
         fitchParsimonyRecursive(tree, root2, root1) +
         localParsimony(tree, root1, root2, -1);
}

void destroyGlobalAuxSequences() {
  destroySequence(unionSeq);
  destroySequence(interSeq);
}
