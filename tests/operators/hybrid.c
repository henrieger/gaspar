#include <assert.h>
#include <config.h>
#include <operators/hybrid.h>
#include <sequence-alignment/sequence-alignment.h>
#include <stdlib.h>
#include <time.h>
#include <tree/iterator.h>
#include <tree/tree.h>

int main() {
  srand(time(NULL));

  const uint64_t taxa = 5;
  const uint64_t characters = 64;
  const uint64_t states = 2;

  char *labels[] = {"A", "B", "C", "D", "E"};
  alignment_t *alignment = newAlignment(taxa, characters, states, labels);

  tree_t *tree = newTree(alignment);
  int32_t *oldTreeParent = tree->parent;
  int32_t *oldTreeLeft = tree->left;
  int32_t *oldTreeRight = tree->right;

  // Create the structure of the tree
  // (A,((D,C),(B,E)))
  int32_t treeParent[] = {-1, 0, 1, 1, 0, 3, 2, 2, 3};
  int32_t treeLeft[] = {4, 2, 7, 5, -1, -1, -1, -1, -1};
  int32_t treeRight[] = {1, 3, 6, 8, -1, -1, -1, -1, -1};
  tree->parent = treeParent;
  tree->left = treeLeft;
  tree->right = treeRight;

  // Repeat various random hybrid operations
  treeIterator_t *it = newTreeIterator(tree);
  config_t config = {.hybrid_nniProb = 0.5};
  for (int i = 0; i < 100; i++) {
    resetTreeIterator(it);
    hybridOp(tree, &config);
    assert(tree->parent[0] == NULL_EDGE);
    assert(tree->left[0] == 4);
    assert(tree->right[0] < 4);
    for (int32_t node = nextTreeIterator(it); node != NULL_EDGE;
         node = nextTreeIterator(it))
      ;
  }
  destroyIterator(it);

  tree->parent = oldTreeParent;
  tree->left = oldTreeLeft;
  tree->right = oldTreeRight;
  destroyTree(tree);
  destroyAlignment(alignment);
}
