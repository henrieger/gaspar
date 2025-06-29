#include "parsimony.h"

#include <config.h>
#include <sequence-alignment/mask-operations.h>
#include <sequence-alignment/sequence-alignment.h>
#include <stdlib.h>
#include <tree/tree.h>

sequence_t *unionSeq;
sequence_t *interSeq;
stateAllowedMask_t *r, *notR, *aux1, *aux2;
unsigned long parsimonyCalls;

void initializeGlobalAuxSequences() {
  unionSeq = newSequence();
  interSeq = newSequence();
  r = newAllowedStates();
  notR = newAllowedStates();
  aux1 = newAllowedStates();
  aux2 = newAllowedStates();
}

int scoreFromInters(stateAllowedMask_t *r) {
  int score = 0;
  int seqSizeInBytes = (7 + getSequenceSize()) / 8;

  char *charR = (char *)r;

  for (int i = 0; i < seqSizeInBytes; i++) {
    score += getCumulativeWeights(i, ~(charR[i]) & 0xff);
  }

  return score;
}

int localParsimony(tree_t *tree, int n1, int n2, int node) {
  stateAllowedMask_t **mask1 = tree->nodes[n1].sequence->stateAllowedMask;
  stateAllowedMask_t **mask2 = tree->nodes[n2].sequence->stateAllowedMask;

  int arraySize = allowedArraySize();

  for (int i = 0; i < arraySize; i++)
    r[i] = 0;

  for (int i = 0; i < CHAR_STATES; i++) {
    // U = n1.sequence | n2.sequence
    maskUnion(unionSeq->stateAllowedMask[i], mask1[i], mask2[i]);

    // I = n1.sequence & n2.sequence
    maskIntersection(interSeq->stateAllowedMask[i], mask1[i], mask2[i]);
    // R = U(I)
    maskUnion(r, r, interSeq->stateAllowedMask[i]);
  }

  if (node > 0) {
    for (int i = 0; i < CHAR_STATES; i++) {
      // n.sequence = (I & R) | (U & ~R)
      maskIntersection(aux1, interSeq->stateAllowedMask[i], r);
      maskNot(notR, r);
      maskIntersection(aux2, unionSeq->stateAllowedMask[i], notR);
      maskUnion(tree->nodes[node].sequence->stateAllowedMask[i], aux1, aux2);
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
  if (nodeStruct->edges[0] == from) {
    n1 = nodeStruct->edges[1];
    n2 = nodeStruct->edges[2];
  } else if (nodeStruct->edges[1] == from) {
    n1 = nodeStruct->edges[0];
    n2 = nodeStruct->edges[2];
  } else if (nodeStruct->edges[2] == from) {
    n1 = nodeStruct->edges[0];
    n2 = nodeStruct->edges[1];
  }

  return fitchParsimonyRecursive(tree, n1, node) +
         fitchParsimonyRecursive(tree, n2, node) +
         localParsimony(tree, n1, n2, node);
}

// Calculate Wagner parsimony of a tree using Fitch's algorithm (Fitch, 1971).
int fitchParsimony(tree_t *tree, config_t *config) {
  if (!tree)
    return 0;

  parsimonyCalls++;

  int root1 = tree->root;
  int root2 = tree->nodes[tree->root].edges[0];

  return fitchParsimonyRecursive(tree, root1, root2) +
         fitchParsimonyRecursive(tree, root2, root1) +
         localParsimony(tree, root1, root2, -1);
}

void destroyGlobalAuxSequences() {
  destroySequence(unionSeq);
  destroySequence(interSeq);
  free(r);
  free(notR);
  free(aux1);
  free(aux2);
}

inline void resetParsimonyCalls() { parsimonyCalls = 0; }

inline unsigned long getParsimonyCalls() { return parsimonyCalls; }
