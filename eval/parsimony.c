#include "parsimony.h"

#include <avx2/avx2.h>
#include <sequence-alignment/sequence-alignment.h>
#include <stdint.h>
#include <stdio.h>
#include <tree/tree.h>

// Calculate parsimony of subtree, keeping track of origin of call.
int fitch_parsimony_recursive(tree_t *tree) {
  // Leaf result is always valid and equal to 0 (no change within a single node)
  if (!tree || isLeaf(tree))
    return 0;

  // Iterate through all children and check if any result is invalid
  int score = 0;
  uint8_t validScore = 1;

  // For each child, get its individual parsimony score and check if it was
  // recently rescored
  for (node_t *n = tree->next; n != tree; n = n->next) {
    score += fitch_parsimony_recursive(n->out);

    if (!n->out->info->validSequence)
      validScore = 0;

    // Acknowledge validity of new result in child
    n->out->info->validSequence = 1;
  }

  // If no results are invalid, return the currently calculated score
  if (validScore)
    return tree->info->parsimonyScore;

  // If some child is invalid, invalidate self and proceed
  tree->info->validSequence = 0;

  // Create auxiliary sequences for the calculations of the new sequence states
  for (int i = 0; i < getPaddedSequenceSize(); i += 32) {
    avx_t avx_union = _mm256_setzero_si256();
    avx_t avx_intersection = _mm256_set1_epi8(-1);

    avx_store(unionSequence->charsets, avx_union, i);
    avx_store(intersectionSequence->charsets, avx_intersection, i);
  }

  // Calculate union and intersection for each site in sequence
  for (node_t *n = tree->next; n != tree; n = n->next) {
    for (int i = 0; i < getPaddedSequenceSize(); i += 32) {
      avx_t avx_intersection = avx_load(intersectionSequence->charsets, i);
      avx_t avx_union = avx_load(unionSequence->charsets, i);
      avx_t avx_sequence = avx_load(n->out->info->sequence->charsets, i);

      // Calculate union and intersection of states
      avx_union = avx_or(avx_sequence, avx_union);
      avx_intersection = avx_and(avx_sequence, avx_intersection);

      avx_store(unionSequence->charsets, avx_union, i);
      avx_store(intersectionSequence->charsets, avx_intersection, i);
    }
  }

  for (int i = 0; i < getPaddedSequenceSize(); i += 32) {
    avx_t avx_intersection = avx_load(intersectionSequence->charsets, i);
    avx_t avx_union = avx_load(unionSequence->charsets, i);

    // Compute a bitmask for sequence operations
    avx_t mask = avx_setMask(avx_intersection);

    // Define new sequence with intersections and unions
    avx_t unionMask = avx_and(avx_union, mask);
    avx_t sequence = avx_or(unionMask, avx_intersection);

    avx_store(tree->info->sequence->charsets, sequence, i);
  }

  // Increment the score by the weight for each empty intersection
  for (int i = 0; i < getSequenceSize(); i++)
    score += !(intersectionSequence->charsets[i]) * getCharacterWeight(i);

  tree->info->parsimonyScore = score;
  return tree->info->parsimonyScore;
}

// Calculate Wagner parsimony of a tree using Fitch's algorithm (Fitch, 1971).
int fitch_parsimony(tree_t *tree) {
  if (!tree->out)
    return fitch_parsimony_recursive(tree);

  sequence_t *root = tree->info->sequence;
  sequence_t *out = tree->out->info->sequence;

  int score =
      fitch_parsimony_recursive(tree) + fitch_parsimony_recursive(tree->out);
  for (int i = 0; i < getSequenceSize(); i++)
    score += !(root->charsets[i] & out->charsets[i]) * getCharacterWeight(i);

  return score;
}
