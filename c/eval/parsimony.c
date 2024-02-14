#include "parsimony.h"

#include <sequence-alignment/sequence-alignment.h>
#include <tree/tree.h>
#include <stdint.h>
#include <stdlib.h>

// Calculate parsimony of subtree, keeping track of origin of call.
int fitch_parsimony_recursive(tree_t *tree, node_t *from) {
  // Leaf result is always valid and equal to 0 (no change with a single node)
  if (!tree || isLeaf(tree))
    return 0;

  // Iterate through all nodes and check if any result is invalid
  int score = 0;
  uint8_t validScore = 1;

  // If function wasn't called from outside (i.e. call of unrooted tree), also
  // calculate parsimony of out
  if (tree->out != from) {
    score += fitch_parsimony_recursive(tree->out, tree);
    if (!tree->out->info->validSequence)
      validScore = 0;

    // Acknowledge validity of new result in child
    tree->out->info->validSequence = 1;
  }

  // For each child, get its individual parsimony score and check if it was
  // recently rescored
  for (node_t *n = tree->next; n != tree; n = n->next) {
    score += fitch_parsimony_recursive(n->out, n);
    if (!n->out->info->validSequence)
      validScore = 0;

    // Acknowledge validity of new result in child
    n->out->info->validSequence = 1;
  }

  // If result of some child is invalid, invalidate self and recalculate score
  if (!validScore) {
    tree->info->validSequence = 0;

    for (int i = 0; i < getSequenceSize(); i++) {
      charset_t unionCharset = CHARSET_EMPTY;
      charset_t intersectionCharset = CHARSET_FULL;

      if (tree->out != from) {
        tree->out->info->validSequence = 1;
        unionCharset |= tree->out->info->sequence->charsets[i];
        intersectionCharset &= tree->out->info->sequence->charsets[i];
      }

      for (node_t *n = tree->next; n != tree; n = n->next) {
        // Calculate union and intersection of states
        unionCharset |= n->out->info->sequence->charsets[i];
        intersectionCharset &= n->out->info->sequence->charsets[i];
      }

      // If there is a non-empty intersection, set that character as it.
      // Else, set it as the union and increment the score of the node by the
      // character weight
      if (intersectionCharset) {
        tree->info->sequence->charsets[i] = intersectionCharset;
      } else {
        tree->info->sequence->charsets[i] = unionCharset;
        score += getCharacterWeight(i);
      }
    }

    tree->info->parsimonyScore = score;
  }

  return tree->info->parsimonyScore;
}

// Calculate Wagner parsimony of a tree using Fitch's algorithm (Fitch, 1971).
int fitch_parsimony(tree_t *tree) {
  return fitch_parsimony_recursive(tree, NULL);
}
