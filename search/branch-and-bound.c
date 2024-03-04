#include "branch-and-bound.h"

#include <answer/answer.h>
#include <sequence-alignment/sequence-alignment.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tree/tree.h>

int numTreesTest = 30; // TODO: define global number of trees in answer;

void branchAndBoundRecursive(tree_t *tree, alignment_t alignment,
                             int eval_fn(tree_t *), int sequenceIndex,
                             answer_t *answer, node_t *from);

// Apply a new node to designated branch and call for next step
void subroutineBNB(node_t *node, tree_t *tree, alignment_t alignment,
                   int eval_fn(tree_t *), int currEval, int sequenceIndex,
                   answer_t *answer, node_t *from) {
  node_t *new = addBrother(node, alignment[sequenceIndex].label);
  new->info->sequence = copySequence(alignment + sequenceIndex);
  if (currEval <= getScore(answer))
    branchAndBoundRecursive(tree, alignment, eval_fn, sequenceIndex + 1, answer,
                            tree);
  prune(new);
  destroyTree(new);
}

void branchAndBoundRecursive(tree_t *tree, alignment_t alignment,
                             int eval_fn(tree_t *), int sequenceIndex,
                             answer_t *answer, node_t *from) {
  // No need to execute function in leaves
  if (!tree || isLeaf(tree))
#ifdef DEBUG
  {
    printf("Bounced on tree: ");
    printTree(tree);
    printf("\n");
    return;
  }
#else
    return;
#endif

  // Evaluate a full tree and update answer accordingly
  int evalValue = eval_fn(tree);
  if (sequenceIndex == getAlignmentSize()) {
    if (evalValue < getScore(answer))
      resetAndUpdateScore(answer, evalValue);
    insertAnswer(answer, tree);
    return;
  }

#ifdef DEBUG
  printf("Searching tree: ");
  printTree(tree);
  printf(" - %d\n", evalValue);
#endif

  // If in tree root, apply function to out node as well
  if (tree->out != from) {
    subroutineBNB(tree->out, tree, alignment, eval_fn, evalValue, sequenceIndex,
                  answer, tree);
  }

  // Apply recursion to every child
  for (node_t *n = tree->next; n->next != tree; n = n->next) {
    subroutineBNB(n->out, tree, alignment, eval_fn, evalValue, sequenceIndex,
                  answer, n);
  }
}

// Realizes a branch and bound search with given alignment and eval function
answer_t *branchAndBoundSearch(alignment_t alignment, int eval_fn(tree_t *)) {
  if (getAlignmentSize() < 3)
    return NULL;

  tree_t *baseTree = smallUnrootedTree(alignment[0].label, alignment[1].label,
                                       alignment[2].label);

  node_t *node0 = searchNodeByName(baseTree, alignment[0].label);
  node_t *node1 = searchNodeByName(baseTree, alignment[1].label);
  node_t *node2 = searchNodeByName(baseTree, alignment[2].label);

  node0->info->sequence = copySequence(alignment + 0);
  node1->info->sequence = copySequence(alignment + 1);
  node2->info->sequence = copySequence(alignment + 2);

  printTree(baseTree);
  printf("\n");

  answer_t *answer = initializeAnswer(numTreesTest);
  branchAndBoundRecursive(baseTree, alignment, eval_fn, 3, answer, NULL);
  return answer;
}
