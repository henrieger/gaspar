#include "parsimony.h"

#include <sequence-alignment/sequence-alignment.h>
#include <tree/tree.h>

// Calculate parsimony of subtree, keeping track of origin of call.
int fitch_parsimony_recursive(tree_t *tree) {
  // Leaf result is always valid and equal to 0 (no change within a single node)
  if (!tree || isLeaf(tree))
    return 0;

  // Iterate through all nodes
  int score = 0;

  // For each child, get its individual parsimony score and add to total
  for (node_t *n = tree->next; n != tree; n = n->next)
    score += fitch_parsimony_recursive(n->out);

  // Calculate self sequence and add changes to score
  for (int i = 0; i < getSequenceSize(); i++) {
    charset_t unionCharset = CHARSET_EMPTY;
    charset_t intersectionCharset = CHARSET_FULL;

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
  return score;
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
