#include <assert.h>
#include <config.h>
#include <operators/subtree-swap.h>
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

  // Swap B and C
  // (A,((D,B),(C,E)))
  subtreeSwap(tree, 5, 6);
  treeIterator *it = newTreeIterator(tree);
  for (int32_t node = nextTreeIterator(it); node != NULL_EDGE;
       node = nextTreeIterator(it))
    ;
  assert(isSisterNode(tree, 6, 8));
  assert(isSisterNode(tree, 7, 5));
  assert(isSisterNode(tree, tree->parent[6], tree->parent[7]));
  assert(isSisterNode(tree, 4, tree->parent[tree->parent[6]]));

  // Swap (D,B) and (C,E)
  // Should result in the same tree
  // (A,((D,B),(C,E)))
  subtreeSwap(tree, 5, 7);
  resetTreeIterator(it);
  for (int32_t node = nextTreeIterator(it); node != NULL_EDGE;
       node = nextTreeIterator(it))
    ;
  assert(isSisterNode(tree, 6, 8));
  assert(isSisterNode(tree, 7, 5));
  assert(isSisterNode(tree, tree->parent[6], tree->parent[7]));
  assert(isSisterNode(tree, 4, tree->parent[tree->parent[6]]));

  // Now do some random ones!
  config_t config = {};
  for (int i = 0; i < 100; i++) {
    resetTreeIterator(it);
    randomSubtreeSwap(tree, &config);
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
