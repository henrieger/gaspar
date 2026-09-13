#include <gaspar/operators/spr.h>

#include <gaspar/base/config.h>
#include <gaspar/sequence-alignment/sequence-alignment.h>
#include <gaspar/tree/iterator.h>
#include <gaspar/tree/tree.h>

#include <assert.h>
#include <stdlib.h>
#include <time.h>

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

  // Prune D and graft it on E
  // (A,(C,(B,(D,E))))
  subtreePrune(tree, 2, 7);
  subtreeGraft(tree, 2, 7, 3, 8);
  treeIterator_t *it = newTreeIterator(tree);
  for (int32_t node = nextTreeIterator(it); node != NULL_EDGE;
       node = nextTreeIterator(it))
    ;
  assert(isSisterNode(tree, 7, 8));
  assert(isSisterNode(tree, 5, tree->parent[7]));
  assert(isSisterNode(tree, 6, tree->parent[5]));
  assert(isSisterNode(tree, 4, tree->parent[6]));

  // Prune D and graft it on B
  // (A,(C,((D,B),E)))
  subtreePrune(tree, 2, 7);
  subtreeGraft(tree, 2, 7, 3, 5);
  resetTreeIterator(it);
  for (int32_t node = nextTreeIterator(it); node != NULL_EDGE;
       node = nextTreeIterator(it))
    ;
  assert(isSisterNode(tree, 7, 5));
  assert(isSisterNode(tree, 8, tree->parent[5]));
  assert(isSisterNode(tree, 6, tree->parent[8]));
  assert(isSisterNode(tree, 4, tree->parent[6]));

  // Prune E, regraft onto B
  // (A,(C,(D,(B,E))))
  subtreePrune(tree, 3, 8);
  subtreeGraft(tree, 3, 8, 2, 5);
  resetTreeIterator(it);
  for (int32_t node = nextTreeIterator(it); node != NULL_EDGE;
       node = nextTreeIterator(it))
    ;
  assert(isSisterNode(tree, 5, 8));
  assert(isSisterNode(tree, 7, tree->parent[5]));
  assert(isSisterNode(tree, 6, tree->parent[7]));
  assert(isSisterNode(tree, 4, tree->parent[6]));

  // Now do some random ones!
  config_t config;
  for (int i = 0; i < 100; i++) {
    resetTreeIterator(it);
    randomSPR(tree, &config);
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
