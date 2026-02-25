#include "parsimony.h"

#include <config.h>
#include <sequence-alignment/sequence-alignment.h>
#include <stdint.h>
#include <tree/tree.h>
#include <utils/math.h>

uint64_t parsimonyCalls;

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

  uint64_t **maskLeft =
      isLeaf(tree, tree->left[node])
          ? (uint64_t **)(tree->alignment
                              ->sequenceMasks[tree->left[node] -
                                              treeInternalNodes(tree)])
          : (uint64_t **)(tree->internalSequences[tree->left[node]]);
  uint64_t **maskRight =
      isLeaf(tree, tree->right[node])
          ? (uint64_t **)(tree->alignment
                              ->sequenceMasks[tree->right[node] -
                                              treeInternalNodes(tree)])
          : (uint64_t **)(tree->internalSequences[tree->right[node]]);

  // U = n1.sequence | n2.sequence
  // I = n1.sequence & n2.sequence

  // R = Uniorium(I)
  uint64_t maskSize =
      ceilDiv(allowedArraySize(tree->alignment->characters), sizeof(uint64_t));
  uint64_t r[maskSize];
  for (int j = 0; j < maskSize; j++) {
    r[j] = 0;
  }
  for (int i = 0; i < tree->alignment->states; i++) {
    for (int j = 0; j < maskSize; j++) {
      r[j] |= (maskLeft[i][j] & maskRight[i][j]);
    }
  }

  // n.sequence = (I & R) | (U & ~R)
  uint64_t **treeSeq64 = (uint64_t **)tree->internalSequences[node];
  for (int i = 0; i < tree->alignment->states; i++) {
    for (int j = 0; j < maskSize; j++) {
      treeSeq64[i][j] = (maskLeft[i][j] & maskRight[i][j] & r[j]) |
                        ((maskLeft[i][j] | maskRight[i][j]) & ~r[j]);
    }
  }

  return scoreFromIntersection((stateAllowedMask_t *)r, tree->alignment);
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

inline void resetParsimonyCalls() { parsimonyCalls = 0; }

inline uint64_t getParsimonyCalls() { return parsimonyCalls; }
