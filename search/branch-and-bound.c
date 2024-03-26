#include "branch-and-bound.h"

#include <answer/answer.h>
#include <sequence-alignment/sequence-alignment.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tree/tree.h>

alignment_t auxAlignment; // "Alignment" of internal nodes for saving intermediary sequences

int numTreesTest = 30; // TODO: define global number of trees in answer;

// Recursive branch and bound search, keeping track of origin (root) of tree
void branchAndBoundRecursive(node_t *node, tree_t *root, alignment_t alignment,
                             int eval_fn(tree_t *), int sequenceIndex,
                             answer_t *answer);

// Subroutine to recursevely add and remove nodes to each branch
void subroutineBNB(node_t *node, tree_t *root, alignment_t alignment,
                   int eval_fn(tree_t *), int sequenceIndex, answer_t *answer) {
  // Insert in this branch
  node_t *new = addBrother(node, alignment[sequenceIndex].label);
  new->info->sequence = alignment + sequenceIndex;
  new->out->info->sequence = auxAlignment + sequenceIndex - 2; 
  // Repeat recursion
  branchAndBoundRecursive(root, root, alignment, eval_fn, sequenceIndex + 1,
                          answer);

// Delete new node
#ifdef DEBUG
  printf("Removing node %s from bnb\n", new->info->name);
#endif
  node_t *old = prune(new);
  destroyTree(new);
  old->info->validSequence = 0;

  // Order children to also insert
  branchAndBoundRecursive(node->out, root, alignment, eval_fn, sequenceIndex,
                          answer);
}

// Recursive branch and bound search, keeping track of origin (root) of tree
void branchAndBoundRecursive(node_t *node, tree_t *root, alignment_t alignment,
                             int eval_fn(tree_t *), int sequenceIndex,
                             answer_t *answer) {
  // Evaluate tree and bound if already greater than current score
  int score = eval_fn(root);

#ifdef DEBUG
  printf("Searching tree: ");
  printTree(root);
  printf(" - Score: %d\n", score);
#endif

  // Reference nodes cannot be leaves
  if (!node || !root || isLeaf(node))
    return;

  // Bound if already greater than already calculated
  if (score > getScore(answer))
    return;

  // If already in last taxon, update answer
  if (sequenceIndex == getAlignmentSize()) {
    updateAnswer(answer, root, score);
    return;
  }

  // Insert a new node in every branch
  for (node_t *n = node->next; n != node; n = n->next) {
    subroutineBNB(n, root, alignment, eval_fn, sequenceIndex, answer);
  }

  // If root repeat procedure for out
  if (node == root) {
    subroutineBNB(root, root, alignment, eval_fn, sequenceIndex, answer);
  }
}

// Performs a branch and bound search with given alignment and eval function
answer_t *branchAndBoundSearch(alignment_t alignment, int eval_fn(tree_t *)) {
  if (getAlignmentSize() < 3)
    return NULL;

  // Initialize alignment of internal nodes
  auxAlignment = newAlignment();

  // Initialize base recursion tree
  tree_t *baseTree = smallUnrootedTree(alignment[0].label, alignment[1].label,
                                       alignment[2].label);
  node_t *node0 = searchNodeByName(baseTree, alignment[0].label);
  node_t *node1 = searchNodeByName(baseTree, alignment[1].label);
  node_t *node2 = searchNodeByName(baseTree, alignment[2].label);
  node0->info->sequence = alignment + 0;
  node1->info->sequence = alignment + 1;
  node2->info->sequence = alignment + 2;
  baseTree->info->sequence = auxAlignment + 0;

  // Initialize recursion
  answer_t *answer = initializeAnswer(numTreesTest);
  branchAndBoundRecursive(baseTree, baseTree, alignment, eval_fn, 3, answer);

  // Destroy the alignment of internal nodes
  destroyAlignment(auxAlignment);

  // Destroy base tree
  destroyTree(baseTree);

  return answer;
}
