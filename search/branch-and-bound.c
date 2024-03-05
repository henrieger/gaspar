#include "branch-and-bound.h"

#include <answer/answer.h>
#include <sequence-alignment/sequence-alignment.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tree/tree.h>

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
  new->info->sequence = copySequence(alignment + sequenceIndex);
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
    if (score < getScore(answer)) {
#ifdef DEBUG
      printf("New score : %d - Curr score: %d\n", score, getScore(answer));
#endif
      resetAndUpdateScore(answer, score);
    }
    insertAnswer(answer, root);
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

  // Initialize base recursion tree
  tree_t *baseTree = smallUnrootedTree(alignment[0].label, alignment[1].label,
                                       alignment[2].label);
  node_t *node0 = searchNodeByName(baseTree, alignment[0].label);
  node_t *node1 = searchNodeByName(baseTree, alignment[1].label);
  node_t *node2 = searchNodeByName(baseTree, alignment[2].label);
  node0->info->sequence = copySequence(alignment + 0);
  node1->info->sequence = copySequence(alignment + 1);
  node2->info->sequence = copySequence(alignment + 2);

  // Initialize recursion
  answer_t *answer = initializeAnswer(numTreesTest);
  branchAndBoundRecursive(baseTree, baseTree, alignment, eval_fn, 3, answer);
  return answer;
}
