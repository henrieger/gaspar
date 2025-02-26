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
  tree->nodes[baseNode].edges[0] = n1;
  tree->nodes[baseNode].edges[1] = n2;
  tree->nodes[baseNode].edges[2] = taxon;

  // Associate "root" of new taxon
  tree->nodes[taxon].edges[0] = baseNode;

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

  int oldedges[3];
  oldedges[0] = tree->nodes[node].edges[0];
  oldedges[1] = tree->nodes[node].edges[1];
  oldedges[2] = tree->nodes[node].edges[2];

  if (oldedges[0] >= 0 && oldedges[0] != from)
    addNodeAndProceed(tree, node, oldedges[0], alignment, config, taxon,
                      answer);
  if (oldedges[1] >= 0 && oldedges[1] != from)
    addNodeAndProceed(tree, node, oldedges[1], alignment, config, taxon,
                      answer);
  if (oldedges[2] >= 0 && oldedges[2] != from)
    addNodeAndProceed(tree, node, oldedges[2], alignment, config, taxon,
                      answer);
}

// Performs a branch and bound search with given alignment and eval function.
answer_t *branchAndBoundSearch(alignment_t *alignment, config_t *config) {
  if (getAlignmentSize() < 3)
    return NULL;

  tree_t *tree = smallestTree(alignment);
  answer_t *answer = initializeAnswer(config->answer_size);
  branchAndBoundRecursive(tree, tree->root, alignment, config, 3, -1, answer);

  destroyTree(tree);
  return answer;
}
