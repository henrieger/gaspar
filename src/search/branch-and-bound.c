#include "branch-and-bound.h"

#include <answer/answer.h>
#include <config.h>
#include <sequence-alignment/sequence-alignment.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tree/tree.h>

// Recursive branch and bound search, keeping track of origin of call.
void branchAndBoundRecursive(tree_t *tree, int node, alignment_t *alignment,
                             config_t *config, int taxon, int from,
                             answer_t *answer);

// Performs a DFS in the edge of n1 and n2, then proceed with the search in the
// same level
void addNodeAndProceed(tree_t *tree, int n1, int n2, alignment_t *alignment,
                       config_t *config, int taxon, answer_t *answer) {
  // Determine internal node to be used in operation
  int baseNode = tree->leaves + taxon - 2;

  // Change pointers in the edge to new internal node
  changeEdge(tree, n1, n2, baseNode);
  changeEdge(tree, n2, n1, baseNode);

  // Associate edges of internal node
  tree->nodes[baseNode].edge1 = n1;
  tree->nodes[baseNode].edge2 = n2;
  tree->nodes[baseNode].edge3 = taxon;

  // Associate "root" of new taxon
  tree->nodes[taxon].edge1 = baseNode;

  // Search next taxon with new node in place
  branchAndBoundRecursive(tree, n1, alignment, config, taxon + 1, n1, answer);

  // Undo changes
  changeEdge(tree, n1, baseNode, n2);
  changeEdge(tree, n2, baseNode, n1);

  // Search current taxon in next node of edge
  branchAndBoundRecursive(tree, n2, alignment, config, taxon, n1, answer);
}

void branchAndBoundRecursive(tree_t *tree, int node, alignment_t *alignment,
                             config_t *config, int taxon, int from,
                             answer_t *answer) {
  int score = config->evalFn(tree, config);
  if (score > getScore(answer))
    return;

  if (isLeaf(tree, node))
    return;

  if (taxon >= alignment->taxa) {
    updateAnswer(answer, tree, score);
    return;
  }

  int oldEdge1 = tree->nodes[node].edge1;
  int oldEdge2 = tree->nodes[node].edge2;
  int oldEdge3 = tree->nodes[node].edge3;

  if (oldEdge1 >= 0 && oldEdge1 != from)
    addNodeAndProceed(tree, node, oldEdge1, alignment, config, taxon, answer);
  if (oldEdge2 >= 0 && oldEdge2 != from)
    addNodeAndProceed(tree, node, oldEdge2, alignment, config, taxon, answer);
  if (oldEdge3 >= 0 && oldEdge3 != from)
    addNodeAndProceed(tree, node, oldEdge3, alignment, config, taxon, answer);
}

// Performs a branch and bound search with given alignment and eval function.
answer_t *branchAndBoundSearch(alignment_t *alignment, config_t *config) {
  if (getAlignmentSize() < 3)
    return NULL;

  tree_t *tree = smallestTree(alignment);
  answer_t *answer = initializeAnswer(config->answer_size);
  branchAndBoundRecursive(tree, tree->root, alignment, config, 3, -1, answer);

  return answer;
}
