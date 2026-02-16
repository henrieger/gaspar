#include "parsimony.h"

#include <config.h>
#include <sequence-alignment/mask-operations.h>
#include <sequence-alignment/sequence-alignment.h>
#include <stdint.h>
#include <stdlib.h>
#include <tree/tree.h>

stateAllowedMask_t **unionSeq, **interSeq;
stateAllowedMask_t *r, *notR, *aux1, *aux2;
unsigned long parsimonyCalls;

void initializeGlobalAuxSequences(uint32_t characters, uint32_t states) {
  unionSeq = newSequence(characters, states);
  interSeq = newSequence(characters, states);
  r = malloc(allowedArraySize(characters));
  notR = malloc(allowedArraySize(characters));
  aux1 = malloc(allowedArraySize(characters));
  aux2 = malloc(allowedArraySize(characters));
}

void resetGlobalAuxSequences(uint32_t characters, uint32_t states) {
  for (int i = 0; i < states; i++) {
    for (int j = 0; j < characters; j++) {
      unionSeq[i][j] = interSeq[i][j] = 0;
    }
  }
  for (int i = 0; i < characters; i++) {
    r[i] = notR[i] = aux1[i] = aux2[i] = 0;
  }
}

double characterValue(stateAllowedMask_t *r, int position) {
  int arrayPos = position / (8 * sizeof(stateAllowedMask_t));
  int internalPos = position % (8 * sizeof(stateAllowedMask_t));

  return 1 - ((r[arrayPos] >> internalPos) & 1);
}

double scoreFromIntersection(stateAllowedMask_t *r, alignment_t *alignment) {
  double score = 0;

  for (int i = 0; i < alignment->characters; i++) {
    score += characterValue(r, i);
  }

  return score;
}

double localParsimony(tree_t *tree, uint32_t node) {
  if (node < 0)
    return -1;

  resetGlobalAuxSequences(tree->alignment->characters, tree->alignment->states);

  stateAllowedMask_t **maskLeft =
      isLeaf(tree, tree->left[node])
          ? tree->alignment
                ->sequenceMasks[tree->left[node] - treeInternalNodes(tree)]
          : tree->internalSequences[tree->left[node]];
  stateAllowedMask_t **maskRight =
      isLeaf(tree, tree->right[node])
          ? tree->alignment
                ->sequenceMasks[tree->right[node] - treeInternalNodes(tree)]
          : tree->internalSequences[tree->right[node]];

  // U = n1.sequence | n2.sequence
  for (int i = 0; i < tree->alignment->states; i++)
    maskUnion(unionSeq[i], maskLeft[i], maskRight[i],
              tree->alignment->characters);

  // I = n1.sequence & n2.sequence
  for (int i = 0; i < tree->alignment->states; i++)
    maskIntersection(interSeq[i], maskLeft[i], maskRight[i],
                     tree->alignment->characters);
  // R = U(I)
  for (int i = 0; i < tree->alignment->states; i++)
    maskUnion(r, r, interSeq[i], tree->alignment->characters);

  // n.sequence = (I & R) | (U & ~R)
  for (int i = 0; i < tree->alignment->states; i++) {
    maskIntersection(aux1, interSeq[i], r, tree->alignment->characters);
    maskNot(notR, r, tree->alignment->characters);
    maskIntersection(aux2, unionSeq[i], notR, tree->alignment->characters);
    maskUnion(tree->internalSequences[node][i], aux1, aux2,
              tree->alignment->characters);
  }

  return scoreFromIntersection(r, tree->alignment);
}

// Calculate Wagner parsimony of a tree using Fitch's algorithm (Fitch, 1971).
double fitchParsimony(tree_t *tree, config_t *config) {
  if (!tree)
    return 0;

  parsimonyCalls++;

  // Allocate array with order to calculate the scores
  uint32_t callOrder[treeInternalNodes(tree)];
  double scores[treeNodes(tree)];
  callOrder[0] = 0;
  int lastPos = 1;

  // Perform BFS on internal nodes of the tree
  for (int i = 0; i < treeInternalNodes(tree); i++) {
    if (!isLeaf(tree, tree->left[callOrder[i]]))
      callOrder[lastPos++] = tree->left[callOrder[i]];
    if (!isLeaf(tree, tree->right[callOrder[i]]))
      callOrder[lastPos++] = tree->right[callOrder[i]];
  }

  // Set scores of all leaves to 0
  for (int i = firstLeaf(tree); i < treeNodes(tree); i++) {
    scores[i] = 0;
  }

  // Calculate scores for internal nodes in reverse DFS
  for (int i = treeInternalNodes(tree) - 1; i >= 0; i--) {
    scores[callOrder[i]] = scores[tree->left[callOrder[i]]] +
                           scores[tree->right[callOrder[i]]] +
                           localParsimony(tree, callOrder[i]);
  }

  return scores[0];
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
